/*********************************************************************/
/* File: ApiTestBase.cs                                              */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Base class for integration test suites of Word Case */
/*               REST API. Provides shared HTTP client setup and     */
/*               reusable helper methods for executing API requests. */
/*                                                                   */
/* Notes       - Uses WebApplicationFactory for in-memory test host  */
/*               Centralizes API invocation logic for consistency    */
/*               Ensures all test suites share identical execution   */
/*               behavior and request formatting                     */
/*                                                                   */
/* $Log: ApiTestBase.cs                                              */
/* 1.0  14-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

using System.Net.Http;
using System.Net.Http.Json;
using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;
using StringConversionAPI.Models;

public abstract class ApiTestBase : IClassFixture<WebApplicationFactory<Program>>
{
    //
    // ======================================================
    // SHARED HTTP CLIENT
    // ======================================================
    //

    protected readonly HttpClient Client;

    protected ApiTestBase(WebApplicationFactory<Program> factory)
    {
        Client = factory.CreateClient();
    }

    //
    // ======================================================
    // REUSABLE API HELPER
    // ======================================================
    //

    protected async Task<string> ConvertAsync(string text, int choice)
    {
        var response = await Client.PostAsJsonAsync(
            "/api/WordCase/convert",
            new
            {
                text,
                choice
            });

        response.EnsureSuccessStatusCode();

        var result = await response.Content.ReadFromJsonAsync<ConvertResponse>();
        Assert.NotNull(result);

        return result!.Output;
    }
}