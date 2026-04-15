/**************************************************************************************************
 * File        : BasicConversionTests.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : BasicConversionTests
 *
 * Description : Integration test suite for fundamental Word Case REST API conversions.
 *               Validates core string transformation logic backed by the native C++ engine.
 *
 * Notes       : - Inherits ApiTestBase for shared HTTP client configuration.
 *               - Ensures ASCII casing behavior remains consistent across the P/Invoke boundary.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-14  Nitish Singh    Initial implementation of core casing and reversal tests
 *
 **************************************************************************************************/

using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;

/// <summary>
/// Validates primary casing strategies and standard string reversal.
/// These tests ensure the "Happy Path" for the most common user requests.
/// </summary>
public class BasicConversionTests : ApiTestBase
{
    public BasicConversionTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //===================================================================
    // Standard Case Transformations
    //===================================================================

    [Fact]
    [Trait("Category", "StandardCasing")]
    public async Task Convert_LowerCase_ReturnsAllSmallCharacters()
        => Assert.Equal("hello", await ConvertAsync("HELLO", 3));

    [Fact]
    [Trait("Category", "StandardCasing")]
    public async Task Convert_UpperCase_ReturnsAllCapitalCharacters()
        => Assert.Equal("HELLO", await ConvertAsync("hello", 4));

    [Fact]
    [Trait("Category", "StandardCasing")]
    public async Task Convert_CapitalizeWords_ReturnsTitleCase()
        => Assert.Equal("Hello World", await ConvertAsync("hello world", 2));

    [Fact]
    [Trait("Category", "StandardCasing")]
    public async Task Convert_SentenceCase_ReturnsInitialCapitalOnly()
        => Assert.Equal("Hello world", await ConvertAsync("hELLO WORLD", 5));

    //===================================================================
    // Complex Casing & Ordering
    //===================================================================

    [Fact]
    [Trait("Category", "PatternCasing")]
    public async Task Convert_ToggleCase_InvertsCharacterCasing()
        => Assert.Equal("hEllO", await ConvertAsync("HeLLo", 6));

    [Fact]
    [Trait("Category", "PatternCasing")]
    public async Task Convert_AlternatingCase_ReturnsStaggeredCasing()
        => Assert.Equal("HeLlO WoRlD", await ConvertAsync("hello world", 1));

    [Fact]
    [Trait("Category", "Structural")]
    public async Task Convert_Reverse_ReturnsMirroredString()
        => Assert.Equal("!dlroW olleH", await ConvertAsync("Hello World!", 7));
}