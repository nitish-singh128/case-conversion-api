/*********************************************************************/
/* File: EdgeCaseTests.cs                                            */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Integration test suite for edge case handling in    */
/*               Word Case REST API. Validates system behavior for  */
/*               boundary inputs such as empty strings, whitespace,  */
/*               numeric-only inputs, and special character cases.   */
/*                                                                   */
/* Notes       - Inherits ApiTestBase for shared HTTP client setup   */
/*               Ensures robustness of transformation engine under   */
/*               boundary and non-standard inputs                    */
/*                                                                   */
/* $Log: EdgeCaseTests.cs                                             */
/* 1.0  14-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;

public class EdgeCaseTests : ApiTestBase
{
    public EdgeCaseTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //
    // ======================================================
    // 1. EDGE CASE TESTS
    // ======================================================
    //

    [Fact]
    public async Task Convert_EmptyString()
        => Assert.Equal("", await ConvertAsync("", 3));

    [Fact]
    public async Task Convert_OnlySpaces_RemoveSpaces()
        => Assert.Equal("", await ConvertAsync("   ", 9));

    [Fact]
    public async Task Convert_NumbersOnly()
        => Assert.Equal("12345", await ConvertAsync("12345", 4));

    [Fact]
    public async Task Convert_SpecialCharacters_Reverse()
        => Assert.Equal("$#@!", await ConvertAsync("!@#$", 7));

    [Fact]
    public async Task Convert_OnlyVowels_RemoveVowels()
        => Assert.Equal("", await ConvertAsync("aeiouAEIOU", 8));

    [Fact]
    public async Task Convert_NoVowels()
        => Assert.Equal("bcdfg", await ConvertAsync("bcdfg", 8));
}