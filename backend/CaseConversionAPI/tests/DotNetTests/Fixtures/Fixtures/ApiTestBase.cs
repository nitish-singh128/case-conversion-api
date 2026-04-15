/**************************************************************************************************
 * File        : ApiTestBase.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : ApiTestBase
 *
 * Description : Base infrastructure for Word Case API integration testing.
 *               Provides an in-memory HTTP execution environment to validate
 *               the complete request-to-native-processing pipeline.
 *
 * Notes       : - Implements IClassFixture for efficient reuse of WebApplicationFactory.
 *               - Centralizes HTTP communication, JSON marshalling, and validation logic.
 *               - Ensures consistent API contract verification across all test suites.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-14  Nitish Singh    Initial implementation of API test orchestration layer
 *
 **************************************************************************************************/

using System.Net.Http;
using System.Net.Http.Json;
using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;
using StringConversionAPI.Models;

/// <summary>
/// Provides a shared execution context for all API integration tests.
/// Manages the lifecycle of the in-memory TestServer and provides
/// high-level abstraction for REST interactions.
/// </summary>
public abstract class ApiTestBase : IClassFixture<WebApplicationFactory<Program>>
{
    //===================================================================
    // Infrastructure Members
    //===================================================================

    /// <summary>
    /// Virtualized HTTP Client used to dispatch requests to the 
    /// in-memory WebApplicationFactory host.
    /// </summary>
    protected readonly HttpClient Client;

    /// <summary>
    /// Initializes a new instance of the test base with a shared 
    /// application factory.
    /// </summary>
    /// <param name="factory">The virtual host factory for the ASP.NET Core Program.</param>
    protected ApiTestBase(WebApplicationFactory<Program> factory)
    {
        // Configure the client with a base address and handle cookies/redirects
        Client = factory.CreateClient();
    }

    //===================================================================
    // API Orchestration Helpers
    //===================================================================

    /// <summary>
    /// Encapsulates the POST request logic to the conversion endpoint.
    /// Handles JSON serialization, transport, and deserialization of the result.
    /// </summary>
    /// <param name="text">The raw input string to be converted.</param>
    /// <param name="choice">The integer ID of the native conversion strategy.</param>
    /// <returns>The processed string returned by the native C++ engine.</returns>
    /// <exception cref="HttpRequestException">Thrown if the API returns a non-200 status code.</exception>
    protected async Task<string> ConvertAsync(string text, int choice)
    {
        // 1. Dispatch POST request with anonymous DTO
        var response = await Client.PostAsJsonAsync(
            "/api/WordCase/convert",
            new
            {
                text,
                choice
            });

        // 2. Validate HTTP Contract
        response.EnsureSuccessStatusCode();

        // 3. Extract and Validate Payload
        var result = await response.Content.ReadFromJsonAsync<ConvertResponse>();
        
        Assert.NotNull(result);

        // 4. Return Output for Assertion
        return result!.Output;
    }
}