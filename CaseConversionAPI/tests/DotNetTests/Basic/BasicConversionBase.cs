/*********************************************************************/
/* File: BasicConversionTests.cs                                     */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Integration test suite for basic Word Case REST     */
/*               API conversions. Validates core string transformation*/
/*               operations including case conversion, formatting,   */
/*               and reversal logic via REST API layer.             */
/*                                                                   */
/* Notes       - Inherits ApiTestBase for shared HTTP client setup   */
/*               Ensures consistency with C++ reference test suite   */
/*               Covers all fundamental conversion operations        */
/*                                                                   */
/* $Log: BasicConversionTests.cs                                     */
/* 1.0  14-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;

public class BasicConversionTests : ApiTestBase
{
    public BasicConversionTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //
    // ======================================================
    // 1. BASIC CONVERSION TESTS
    // ======================================================
    //

    [Fact]
    public async Task Convert_LowerCase()
        => Assert.Equal("hello", await ConvertAsync("HELLO", 3));

    [Fact]
    public async Task Convert_UpperCase()
        => Assert.Equal("HELLO", await ConvertAsync("hello", 4));

    [Fact]
    public async Task Convert_CapitalizeWords()
        => Assert.Equal("Hello World", await ConvertAsync("hello world", 2));

    [Fact]
    public async Task Convert_SentenceCase()
        => Assert.Equal("Hello world", await ConvertAsync("hELLO WORLD", 5));

    [Fact]
    public async Task Convert_ToggleCase()
        => Assert.Equal("hEllO", await ConvertAsync("HeLLo", 6));

    [Fact]
    public async Task Convert_AlternatingCase()
        => Assert.Equal("HeLlO WoRlD", await ConvertAsync("hello world", 1));

    [Fact]
    public async Task Convert_Reverse()
        => Assert.Equal("!dlroW olleH", await ConvertAsync("Hello World!", 7));
}