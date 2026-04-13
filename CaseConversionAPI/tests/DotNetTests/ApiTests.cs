/*********************************************************************/
/* File: ApiTests.cs                                                 */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Integration test suite for Word Case REST API.      */
/*               Mirrors C++ test suite behavior to ensure           */
/*               cross-layer consistency between API and core        */
/*               string processing engine.                           */
/*                                                                   */
/* Notes       - Uses canonical outputs from C++ tests               */
/*               Covers basic, advanced, edge, and invalid cases     */
/*                                                                   */
/* $Log: ApiTests.cs                                                 */
/* 1.2  14-Apr-2026  Nitish Singh                                    */
/*      Synced with C++ test expectations.                           */
/*********************************************************************/

using System.Net.Http;
using System.Net.Http.Json;
using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;
using StringConversionAPI.Models;

public class ApiTests : IClassFixture<WebApplicationFactory<Program>>
{
    private readonly HttpClient _client;

    public ApiTests(WebApplicationFactory<Program> factory)
    {
        _client = factory.CreateClient();
    }

    private async Task<string> ConvertAsync(string text, int choice)
    {
        var response = await _client.PostAsJsonAsync(
            "/api/WordCase/convert",
            new { text, choice });

        response.EnsureSuccessStatusCode();

        var result = await response.Content.ReadFromJsonAsync<ConvertResponse>();
        Assert.NotNull(result);

        return result.Output;
    }

    //
    // ======================================================
    // 1. BASIC CONVERSIONS (MATCH C++ TESTS)
    // ======================================================
    //

    [Fact]
    public async Task Convert_LowerCase()
    {
        var output = await ConvertAsync("HELLO", 3);
        Assert.Equal("hello", output);
    }

    [Fact]
    public async Task Convert_UpperCase()
    {
        var output = await ConvertAsync("hello", 4);
        Assert.Equal("HELLO", output);
    }

    [Fact]
    public async Task Convert_CapitalizeWords()
    {
        var output = await ConvertAsync("hello world", 2);
        Assert.Equal("Hello World", output);
    }

    [Fact]
    public async Task Convert_SentenceCase()
    {
        var output = await ConvertAsync("hELLO WORLD", 5);
        Assert.Equal("Hello world", output);
    }

    [Fact]
    public async Task Convert_ToggleCase()
    {
        var output = await ConvertAsync("HeLLo", 6);
        Assert.Equal("hEllO", output);
    }

    [Fact]
    public async Task Convert_AlternatingCase()
    {
        var output = await ConvertAsync("hello world", 1);
        Assert.Equal("HeLlO WoRlD", output);
    }

    [Fact]
    public async Task Convert_Reverse()
    {
        var output = await ConvertAsync("Hello World!", 7);
        Assert.Equal("!dlroW olleH", output);
    }

    //
    // ======================================================
    // 2. ADVANCED CONVERSIONS (MATCH C++ TESTS)
    // ======================================================
    //

    [Fact]
    public async Task Convert_InvertWords()
    {
        var output = await ConvertAsync("Hello World", 10);
        Assert.Equal("olleH dlroW", output);
    }

    [Fact]
    public async Task Convert_SnakeCase()
    {
        var output = await ConvertAsync("Hello World Example", 11);
        Assert.Equal("hello_world_example", output);
    }

    [Fact]
    public async Task Convert_KebabCase()
    {
        var output = await ConvertAsync("Hello World Example", 12);
        Assert.Equal("hello-world-example", output);
    }

    [Fact]
    public async Task Convert_RemoveSpaces()
    {
        var output = await ConvertAsync("Hello World", 9);
        Assert.Equal("HelloWorld", output);
    }

    [Fact]
    public async Task Convert_RemoveVowels()
    {
        var output = await ConvertAsync("Hello World", 8);
        Assert.Equal("Hll Wrld", output);
    }

    [Fact]
    public async Task Convert_LeetSpeak()
    {
        var output = await ConvertAsync("Test", 13);
        Assert.Equal("7357", output);
    }

    //
    // ======================================================
    // 3. EDGE CASES (MATCH C++ TESTS)
    // ======================================================
    //

    [Fact]
    public async Task Convert_EmptyString()
    {
        var output = await ConvertAsync("", 3);
        Assert.Equal("", output);
    }

    [Fact]
    public async Task Convert_OnlySpaces_RemoveSpaces()
    {
        var output = await ConvertAsync("   ", 9);
        Assert.Equal("", output);
    }

    [Fact]
    public async Task Convert_NumbersOnly()
    {
        var output = await ConvertAsync("12345", 4);
        Assert.Equal("12345", output);
    }

    [Fact]
    public async Task Convert_SpecialCharacters_Reverse()
    {
        var output = await ConvertAsync("!@#$", 7);
        Assert.Equal("$#@!", output);
    }

    [Fact]
    public async Task Convert_OnlyVowels_RemoveVowels()
    {
        var output = await ConvertAsync("aeiouAEIOU", 8);
        Assert.Equal("", output);
    }

    [Fact]
    public async Task Convert_NoVowels()
    {
        var output = await ConvertAsync("bcdfg", 8);
        Assert.Equal("bcdfg", output);
    }

    //
    // ======================================================
    // 4. INVALID INPUT (IMPORTANT CONTRACT): 
    // Return original string for invalid choice
    // This is different from C++ CLI application
    // which returns the lower case for invalid choices. 
    // We want to preserve the original string
    // ======================================================
    //

    [Fact]
    public async Task Convert_InvalidChoice_FallsBackToLower()
    {
        var output = await ConvertAsync("Hello", 99);
        Assert.Equal("Hello", output);
    }
}