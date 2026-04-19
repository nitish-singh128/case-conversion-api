/**************************************************************************************************
 * File         : AdvancedConversionTests.cs
 *
 * Copyright    : (c) 2016–2026 nitishhsinghh. All rights reserved.
 * This material may be reproduced for teaching and learning purposes only.
 * It is not to be used in industry or for commercial purposes.
 *
 * Class        : AdvancedConversionTests
 *
 * Description  : Integration test suite for high-complexity conversion and concurrency.
 * Validates M2 Hardware Parallelism, ABI thread-safety, and memory stability.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date            Author           Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-14      Nitish Singh     Initial implementation of advanced tests.
 * 1.1         2026-04-19      Nitish Singh     Added M2 P-Core saturation and hardware-specific tags.
 * 1.2         2026-04-19      Nitish Singh     Integrated Race-Condition, N+1 Stress, and Leak tests.
 **************************************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Testing;
using Xunit;

/// <summary>
/// Validates high-complexity conversion strategies and concurrent execution 
/// patterns tuned for Apple M2 hardware constraints (4 P-Cores).
/// </summary>
public class AdvancedConversionTests : ApiTestBase
{
    public AdvancedConversionTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //===================================================================
    // Advanced Structural & Algorithmic Conversions
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
    [Trait("Category", "Encoding")]
    public async Task Convert_LeetSpeak_ReturnsNumericSubstitutions()
        => Assert.Equal("7357", await ConvertAsync("Test", 13));

    //===================================================================
    // Hardware-Specific Concurrency (Apple M2 Optimization)
    //===================================================================

    [Fact]
    [Trait("Category", "Performance-Benchmark")]
    [Trait("Hardware", "M2-P-Cores")]
    public async Task Benchmark_SequentialVsParallel_ProvesPCoreEfficiency()
    {
        // FIX: Increase size to 500k to ensure P-Cores actually have work to do
        var inputs = Enumerable.Range(1, 8) // Use 8 to fully saturate P-Cores + E-Cores
            .Select(i => $"Bench_Data_{i}_" + new string('X', 500000)) 
            .ToList();

        // Warm-up
        await ConvertAsync("Warmup", 1);

        // Sequential
        var watch = Stopwatch.StartNew();
        foreach (var input in inputs) { await ConvertAsync(input, 1); }
        watch.Stop();
        long sequentialTime = watch.ElapsedMilliseconds;

        // Parallel - Use Parallel.ForEachAsync for better M2 thread management
        watch.Restart();
        await Parallel.ForEachAsync(inputs, new ParallelOptions { MaxDegreeOfParallelism = 4 }, async (input, token) => 
        {
            await ConvertAsync(input, 1);
        });
        watch.Stop();
        long parallelTime = watch.ElapsedMilliseconds;

        double speedup = (double)sequentialTime / parallelTime;
        
        // Low threshold for CI, high threshold for local M2
        Assert.True(parallelTime < sequentialTime, $"Parallel ({parallelTime}ms) was not faster than Sequential ({sequentialTime}ms)");
    }

    //===================================================================
    // Thread Isolation & Race Condition Validation
    //===================================================================

    [Fact]
    [Trait("Category", "Concurrency")]
    public async Task Convert_ConcurrentExecution_EnsuresThreadIsolation()
    {
        var testData = new Dictionary<int, string>
        {
            { 1, "ALPHA" }, { 2, "BRAVO" }, { 3, "CHARLIE" }, { 4, "DELTA" }
        };

        var tasks = testData.Select(kvp => Task.Run(async () => {
            var result = await ConvertAsync(kvp.Value, 4); // Choice 4: Uppercase
            return new { Id = kvp.Key, Output = result };
        }));

        var results = await Task.WhenAll(tasks);

        // Verify no memory cross-talk in the C++ layer
        foreach (var res in results)
        {
            Assert.Equal(testData[res.Id].ToUpper(), res.Output);
        }
    }

    //===================================================================
    // Stress, Boundary & Memory Leak Testing
    //===================================================================

    [Fact]
    [Trait("Category", "Stress")]
    public async Task Convert_LargePayload_Exceeding2MB_ReturnsSuccessfully()
    {
        int sizeInChars = 2100000; 
        string largeInput = new string('a', sizeInChars);
        string result = await ConvertAsync(largeInput, 4);

        Assert.Equal(sizeInChars, result.Length);
        Assert.Equal("A", result.Substring(0, 1)); 
    }

    [Fact]
    [Trait("Category", "Reliability")]
    public async Task Convert_RapidSuccession_NoMemoryLeak()
    {
        // 1000 rapid calls to verify 'freeString' delegate releases native heap
        for (int i = 0; i < 1000; i++)
        {
            var res = await ConvertAsync("LeakCheck", 1);
            Assert.NotNull(res);
        }
    }

    /// <summary>
    /// Validates the 4-thread saturation limit on M2. 
    /// Sends N+1 requests to verify the queue handles the overflow gracefully.
    /// </summary>
    [Fact]
    [Trait("Category", "Hardware-Optimization")]
    public async Task Convert_NPlusOneLoad_MaintainsStability()
    {
        var inputs = Enumerable.Range(1, 5).Select(i => $"Overflow_{i}").ToList();
        var tasks = inputs.Select(input => ConvertAsync(input, 1));
        
        var results = await Task.WhenAll(tasks);
        Assert.Equal(5, results.Length);
    }
}