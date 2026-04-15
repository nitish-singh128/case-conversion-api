/**************************************************************************************************
 * File        : WordCaseController.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : WordCaseController
 *
 * Description : REST API controller exposing string case conversion operations.
 *               Delegates processing to the service layer, which interfaces with
 *               the native C++ conversion engine.
 *
 * Notes       : - Implements HTTP POST endpoint for conversion requests.
 *               - Uses dependency injection for ProcessStringService.
 *               - Supports multiple transformation strategies via native interop.
 *               - Ensures consistent API contract for request/response payloads.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11  Nitish Singh    Initial implementation of API controller
 *
 **************************************************************************************************/

using Microsoft.AspNetCore.Mvc;
using StringConversionAPI.Models;
using StringConversionAPI.Services;

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

        [HttpPost("convert")]
        public IActionResult Convert([FromBody] ConvertRequest request)
        {
            var output = _service.Convert(request.Text, request.Choice);
            var response = new ConvertResponse
            {
                Input = request.Text,
                Choice = request.Choice,
                Output = output ?? string.Empty
            };
            return Ok(response);
        }
    }
}