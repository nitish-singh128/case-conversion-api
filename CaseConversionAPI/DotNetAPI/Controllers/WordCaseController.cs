/*********************************************************************/
/* File: WordCaseController.cs                                       */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - WordCaseController                                  */
/*                                                                   */
/* Description - REST API controller that exposes string case        */
/*               conversion operations. Uses ProcessStringService    */
/*               to delegate conversion logic based on user choice.  */
/*                                                                   */
/* Notes       - Supports multiple conversion strategies including   */
/*               Alternating Case via native C++ interop.            */
/*                                                                   */
/* $Log: WordCaseController.cs                                       */
/* 1.0  11-Apr-2026  Nitish Singh                                   */
/*      Initial revision.                                            */
/*********************************************************************/

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