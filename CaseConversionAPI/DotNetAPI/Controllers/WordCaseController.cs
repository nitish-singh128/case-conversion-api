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