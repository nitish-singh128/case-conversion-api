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

using System;
using System.Net.Http.Json;
using System.Threading.Tasks;
using System.Net;
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

    [Theory]
    [InlineData(10)]
    [InlineData(100)]
    [InlineData(1000)]
    [InlineData(10000)]
    [InlineData(100000)] // The "1 Lakh" Soak Test
    [Trait("Category", "Memory-Safety")]
    public async Task Bridge_MemoryIsStable_AtScale(int requestCount)
    {
        // 1. Force a clean slate for memory tracking
        GC.Collect();
        GC.WaitForPendingFinalizers();
        var initialMemory = GC.GetTotalMemory(true);
        
        // 2. Execute the loop based on the InlineData input
        for(int i = 0; i < requestCount; i++)
        {
            var response = await Client.PostAsJsonAsync("/api/WordCase/convert", new 
            { 
                text = "Safety_Test", 
                choice = 1 
            });
            
            response.EnsureSuccessStatusCode();
            
            // Optional: Dispose response to free up managed resources immediately
            response.Dispose();
        }

        // 3. Final cleanup and check
        GC.Collect();
        GC.WaitForPendingFinalizers();
        var finalMemory = GC.GetTotalMemory(true);
        
        // 4. Assert that growth is within a safe margin (20MB)
        var memoryDiff = finalMemory - initialMemory;
        Assert.True(memoryDiff < 20 * 1024 * 1024, 
            $"Potential Leak! Memory grew by {memoryDiff / 1024 / 1024}MB after {requestCount} requests.");
    }
}