/**************************************************************************************************
 * File        : AdvancedConversionTests.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : AdvancedConversionTests
 *
 * Description : Integration test suite for advanced Word Case REST API conversion scenarios.
 *               Extends the base API infrastructure to validate complex native transformations
 *               including SnakeCase, LeetSpeak, and algorithmic word inversion.
 *
 * Notes       : - Utilizes WebApplicationFactory for in-memory integration testing.
 *               - Validates the full execution path from JSON DTO binding to C++ strategy layer.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-14  Nitish Singh    Initial implementation of advanced conversion tests
 *
 **************************************************************************************************/

using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Testing;
using Xunit;

/// <summary>
/// Validates high-complexity conversion strategies that involve character 
/// replacement, delimiter injection, and structural string manipulation.
/// </summary>
public class AdvancedConversionTests : ApiTestBase
{
    public AdvancedConversionTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //===================================================================
    // Advanced Structural Conversions
    //===================================================================

    [Fact]
    [Trait("Category", "Structural")]
    public async Task Convert_InvertWords_ReturnsReversedWords()
        => Assert.Equal("olleH dlroW", await ConvertAsync("Hello World", 10));

    [Fact]
    [Trait("Category", "Formatting")]
    public async Task Convert_SnakeCase_ReturnsUnderscoreSeparated()
        => Assert.Equal("hello_world_example", await ConvertAsync("Hello World Example", 11));

    [Fact]
    [Trait("Category", "Formatting")]
    public async Task Convert_KebabCase_ReturnsHyphenSeparated()
        => Assert.Equal("hello-world-example", await ConvertAsync("Hello World Example", 12));

    //===================================================================
    // Content Filtering & Optimization
    //===================================================================

    [Fact]
    [Trait("Category", "Filtering")]
    public async Task Convert_RemoveSpaces_ReturnsJoinedString()
        => Assert.Equal("HelloWorld", await ConvertAsync("Hello World", 9));

    [Fact]
    [Trait("Category", "Filtering")]
    public async Task Convert_RemoveVowels_ReturnsConsonantsOnly()
        => Assert.Equal("Hll Wrld", await ConvertAsync("Hello World", 8));

    //===================================================================
    // Algorithmic Substitutions
    //===================================================================

    [Fact]
    [Trait("Category", "Encoding")]
    public async Task Convert_LeetSpeak_ReturnsNumericSubstitutions()
        => Assert.Equal("7357", await ConvertAsync("Test", 13));

    //===================================================================
    // Stress & Boundary Testing (Large Payloads)
    //===================================================================

    [Fact]
    [Trait("Category", "Stress")]
    public async Task Convert_LargePayload_Exceeding2MB_ReturnsSuccessfully()
    {
        // Arrange: Generate ~2.1MB of data (1 character = 1 byte in UTF-8 usually)
        int sizeInChars = 2100000; 
        string largeInput = new string('a', sizeInChars);
        
        // Act: Perform a simple Uppercase conversion (ID 4)
        string result = await ConvertAsync(largeInput, 4);

        // Assert: Verify size integrity and correctness
        Assert.NotNull(result);
        Assert.Equal(sizeInChars, result.Length);
        Assert.Equal("A", result.Substring(0, 1)); // Spot check start
        Assert.Equal("A", result.Substring(result.Length - 1, 1)); // Spot check end
    }
}