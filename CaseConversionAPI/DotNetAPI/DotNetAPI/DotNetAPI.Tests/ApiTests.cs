using System.Net.Http;
using System.Net.Http.Json;
using Xunit;
using Microsoft.AspNetCore.Mvc.Testing;

public class ApiTests : IClassFixture<WebApplicationFactory<Program>>
{
    private readonly HttpClient _client;

    public ApiTests(WebApplicationFactory<Program> factory)
    {
        _client = factory.CreateClient();
    }

    [Fact]
    public async Task Convert_ReturnsUpperCase()
    {
        var response = await _client.PostAsJsonAsync("/convert", new { input = "hello" });

        response.EnsureSuccessStatusCode();

        var result = await response.Content.ReadAsStringAsync();

        Assert.Equal("HELLO", result);
    }
}