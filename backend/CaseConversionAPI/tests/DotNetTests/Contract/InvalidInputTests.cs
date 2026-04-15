/**************************************************************************************************
 * File        : InvalidInputTests.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : InvalidInputTests
 *
 * Description : Integration test suite for defensive input handling within the Word Case REST API.
 *               Validates system resiliency against out-of-range and malformed conversion inputs.
 *
 * Notes       : - Ensures the marshalling layer and native C++ engine fail safely.
 *               - Confirms fallback behavior returns original input (Echo) instead of exceptions.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-14  Nitish Singh    Initial implementation of boundary and resiliency tests
 *
 **************************************************************************************************/

using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;

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
    /// Verifies that an undefined conversion choice (out-of-range integer) 
    /// is handled by the C++ Factory's default case, returning the original
    /// string to prevent API failure.
    /// </summary>
    [Fact]
    [Trait("Category", "Resiliency")]
    public async Task Convert_InvalidChoice_ReturnsOriginalString_SafeFallback()
        => Assert.Equal("Hello", await ConvertAsync("Hello", 99));

    /// <summary>
    /// Verifies behavior when a negative index is passed. 
    /// Ensures consistent fallback behavior across the ABI boundary.
    /// </summary>
    [Fact]
    [Trait("Category", "Resiliency")]
    public async Task Convert_NegativeChoice_ReturnsOriginalString_SafeFallback()
        => Assert.Equal("BoundaryTest", await ConvertAsync("BoundaryTest", -1));
}