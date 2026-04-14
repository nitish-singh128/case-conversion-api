/*********************************************************************/
/* File: AdvancedConversionTests.cs                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Integration test suite for advanced Word Case       */
/*               REST API conversion scenarios.                     */
/*               Extends base API test infrastructure to validate   */
/*               complex string transformation cases including      */
/*               word inversion, case conversion, and formatting.    */
/*                                                                   */
/* Notes       - Inherits ApiTestBase for shared HTTP client setup   */
/*               Ensures consistency with core API contract tests    */
/*               Covers advanced conversion strategies only          */
/*                                                                   */
/* $Log: AdvancedConversionTests.cs                                  */
/* 1.0  14-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Testing;
using Xunit;

public class AdvancedConversionTests : ApiTestBase
{
    public AdvancedConversionTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //
    // ======================================================
    // 1. ADVANCED CONVERSION TESTS
    // ======================================================
    //

    [Fact]
    public async Task Convert_InvertWords()
        => Assert.Equal("olleH dlroW", await ConvertAsync("Hello World", 10));

    [Fact]
    public async Task Convert_SnakeCase()
        => Assert.Equal("hello_world_example", await ConvertAsync("Hello World Example", 11));

    [Fact]
    public async Task Convert_KebabCase()
        => Assert.Equal("hello-world-example", await ConvertAsync("Hello World Example", 12));

    [Fact]
    public async Task Convert_RemoveSpaces()
        => Assert.Equal("HelloWorld", await ConvertAsync("Hello World", 9));

    [Fact]
    public async Task Convert_RemoveVowels()
        => Assert.Equal("Hll Wrld", await ConvertAsync("Hello World", 8));

    [Fact]
    public async Task Convert_LeetSpeak()
        => Assert.Equal("7357", await ConvertAsync("Test", 13));
}