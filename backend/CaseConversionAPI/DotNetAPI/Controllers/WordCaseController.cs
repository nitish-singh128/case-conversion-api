/**************************************************************************************************
 * File         : WordCaseController.cs
 *
 * Copyright    : (c) 2016–2026 nitishhsinghh. All rights reserved.
 * This material may be reproduced for teaching and learning purposes only.
 * It is not to be used in industry or for commercial purposes.
 *
 * Class        : WordCaseController
 *
 * Description  : REST API controller exposing string case conversion operations.
 * Delegates processing to the service layer, which interfaces with
 * the native C++ conversion engine.
 *
 * Notes        : - Implements HTTP POST endpoints for single and parallel batch conversion.
 * - Uses dependency injection for ProcessStringService.
 * - Optimized for Apple M2 P-Core saturation via Parallel.ForEachAsync.
 * - Validates input against the 5MB Security Gate defined in the C++ layer.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date           Author           Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11     Nitish Singh     Initial implementation of API controller.
 * 1.1         2026-04-19     Nitish Singh     Added Parallel Batch Endpoint (4-Thread M2 Support).
 * Integrated async/await for hardware-bound tasks.
 **************************************************************************************************/

using Microsoft.AspNetCore.Mvc;
using StringConversionAPI.Models;
using StringConversionAPI.Services;
using System.Diagnostics;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Linq;

namespace StringConversionAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class WordCaseController : ControllerBase 
    {
        private readonly ProcessStringService _service;

        public WordCaseController(ProcessStringService service)
        {
            _service = service;
        }

        /// <summary>
        /// Single-string conversion endpoint (Sequential).
        /// </summary>
        [HttpPost("convert")]
        public IActionResult Convert([FromBody] ConvertRequest request)
        {
            if (request == null || string.IsNullOrEmpty(request.Text))
                return BadRequest("Invalid request payload.");

            var output = _service.Convert(request.Text, request.Choice);
            
            return Ok(new ConvertResponse 
            {
                Input = request.Text,
                Choice = request.Choice,
                Output = output ?? string.Empty
            });
        }

        /// <summary>
        /// M2-Optimized Parallel Endpoint.
        /// Dispatches work to the Service's 4-thread P-Core saturation logic.
        /// </summary>
        [HttpPost("convert-batch")]
        public async Task<IActionResult> ConvertBatch([FromBody] BatchRequest request)
        {
            if (request == null || request.Texts == null || !request.Texts.Any())
                return BadRequest("Batch payload cannot be empty.");

            // Performance Timing for "Cosine/Wave" Data Analytics
            var stopwatch = Stopwatch.StartNew();

            // v1.3 Service call: Targets 4 Performance Cores
            var results = await _service.ConvertBatchAsync(request.Texts, request.Choice);

            stopwatch.Stop();

            // Return rich data including processing metrics
            return Ok(new 
            {
                Count = request.Texts.Count(),
                Choice = request.Choice,
                Results = results,
                ExecutionTimeMs = stopwatch.ElapsedMilliseconds,
                HardwareTarget = "M2-Performance-Cores (4-Threads)"
            });
        }
    }

    /// <summary>
    /// Model for Parallel Batch Requests.
    /// </summary>
    public class BatchRequest
    {
        public IEnumerable<string> Texts { get; set; } = new List<string>();
        public int Choice { get; set; }
    }
}