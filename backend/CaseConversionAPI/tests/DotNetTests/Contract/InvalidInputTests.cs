/**************************************************************************************************
 * File         : InvalidInputTests.cs
 *
 * Copyright    : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *
 * Description  : Integration test suite for defensive input handling.
 * Updated for v1.1 to validate the 5MB Native Security Gate.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date            Author           Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-14      Nitish Singh     Initial implementation.
 * 1.1         2026-04-19      Nitish Singh     Added 5MB Payload Security Gate validation.
 **************************************************************************************************/

using System.Threading.Tasks;
using System.Net;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;
using System.Net.Http.Json;

/// <summary>
/// Validates system behavior when the API receives input that falls 
/// outside the defined operational parameters.
/// </summary>
public class InvalidInputTests : ApiTestBase
{
    public InvalidInputTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //===================================================================
    // Defensive Boundary Tests
    //===================================================================

    /// <summary>
    /// Verifies that an undefined conversion choice is handled by the 
    /// C++ Factory's default case, returning the original string.
    /// </summary>
    [Fact]
    [Trait("Category", "Resiliency")]
    public async Task Convert_InvalidChoice_ReturnsOriginalString_SafeFallback()
        => Assert.Equal("Hello", await ConvertAsync("Hello", 99));

    /// <summary>
    /// Verifies behavior when a negative index is passed.
    /// </summary>
    [Fact]
    [Trait("Category", "Resiliency")]
    public async Task Convert_NegativeChoice_ReturnsOriginalString_SafeFallback()
        => Assert.Equal("BoundaryTest", await ConvertAsync("BoundaryTest", -1));

    //===================================================================
    // Security & Payload Constraint Tests (M2 Hardware Guardrails)
    //===================================================================

    /// <summary>
    /// Validates the 5MB Security Gate. Inputs exceeding this should trigger 
    /// a Sentinel Check in the service and return a Bad Request.
    /// </summary>
    [Fact]
    [Trait("Category", "Security")]
    public async Task Convert_InputExceeding5MB_ReturnsBadRequest_SentinelTriggered()
    {
        // Arrange
        string oversizedPayload = new string('A', (5 * 1024 * 1024) + 100);

        // Act - Using 'Client' instead of '_client'
        var response = await Client.PostAsJsonAsync("/api/WordCase/convert", new { 
        text = oversizedPayload, 
        choice = 1 
        });
    
        // Assert
        Assert.Equal(HttpStatusCode.BadRequest, response.StatusCode);
        
        var content = await response.Content.ReadAsStringAsync();
        Assert.Contains("5MB security limit", content);
    }

    /// <summary>
    /// Verifies that null/empty inputs are handled gracefully before 
    /// hitting the P/Invoke layer to avoid AccessViolationExceptions.
    /// </summary>
    [Theory]
    [InlineData("")]
    [InlineData(null)]
    [Trait("Category", "Resiliency")]
    public async Task Convert_EmptyOrNull_ReturnsOriginal_PreventsPInvokeCrashing(string input)
    {
        var result = await ConvertAsync(input, 1);
        Assert.Equal(input, result);
    }
}