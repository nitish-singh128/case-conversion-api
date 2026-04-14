/**************************************************************************************************
 * File        : EdgeCaseTests.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : EdgeCaseTests
 *
 * Description : Integration test suite for boundary condition validation in the Word Case REST API.
 *               Ensures system stability when processing empty, non-standard, and symbolic inputs.
 *
 * Notes       : - Validates native C++ engine behavior for zero-length buffers.
 *               - Ensures safe handling of non-alphabetic and special characters.
 *               - Guards against memory access violations and logical inconsistencies.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-14  Nitish Singh    Initial implementation of edge case and boundary tests
 *
 **************************************************************************************************/

using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;

/// <summary>
/// Exhaustive validation of non-standard inputs to ensure no regression 
/// in logic for boundary conditions.
/// </summary>
public class EdgeCaseTests : ApiTestBase
{
    public EdgeCaseTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //===================================================================
    // Null & Whitespace Boundaries
    //===================================================================

    [Fact]
    [Trait("Category", "Boundary")]
    public async Task Convert_EmptyString_ReturnsEmptyResponse()
        => Assert.Equal("", await ConvertAsync("", 3));

    [Fact]
    [Trait("Category", "Boundary")]
    public async Task Convert_OnlySpaces_RemoveSpaces_ReturnsEmptyResponse()
        => Assert.Equal("", await ConvertAsync("   ", 9));

    //===================================================================
    // Character Set Boundaries (Non-Alpha)
    //===================================================================

    [Fact]
    [Trait("Category", "NonAlpha")]
    public async Task Convert_NumbersOnly_MaintainsNumericIntegrity()
        => Assert.Equal("12345", await ConvertAsync("12345", 4));

    [Fact]
    [Trait("Category", "NonAlpha")]
    public async Task Convert_SpecialCharacters_Reverse_HandlesSymbolsCorrectly()
        => Assert.Equal("$#@!", await ConvertAsync("!@#$", 7));

    //===================================================================
    // Domain-Specific Logic Boundaries (Filtering)
    //===================================================================

    [Fact]
    [Trait("Category", "Filtering")]
    public async Task Convert_OnlyVowels_RemoveVowels_ReturnsEmptyString()
        => Assert.Equal("", await ConvertAsync("aeiouAEIOU", 8));

    [Fact]
    [Trait("Category", "Filtering")]
    public async Task Convert_NoVowels_ReturnsOriginalConsonants()
        => Assert.Equal("bcdfg", await ConvertAsync("bcdfg", 8));
}