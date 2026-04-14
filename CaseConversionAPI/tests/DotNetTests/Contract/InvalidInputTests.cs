/*********************************************************************/
/* File: InvalidInputTests.cs                                        */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Integration test suite for invalid input handling   */
/*               in Word Case REST API. Validates system behavior   */
/*               when unsupported or out-of-range conversion choices */
/*               are provided to the API layer.                      */
/*                                                                   */
/* Notes       - Inherits ApiTestBase for shared HTTP client setup   */
/*               Ensures contract compliance for error/fallback cases*/
/*               Aligns with expected API fallback behavior          */
/*                                                                   */
/* $Log: InvalidInputTests.cs                                         */
/* 1.0  14-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

using System.Threading.Tasks;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;

public class InvalidInputTests : ApiTestBase
{
    public InvalidInputTests(WebApplicationFactory<Program> factory)
        : base(factory)
    {
    }

    //
    // ======================================================
    // 1. INVALID INPUT HANDLING TESTS
    // ======================================================
    //

    [Fact]
    public async Task Convert_InvalidChoice_ReturnsOriginalString()
        => Assert.Equal("Hello", await ConvertAsync("Hello", 99));
}