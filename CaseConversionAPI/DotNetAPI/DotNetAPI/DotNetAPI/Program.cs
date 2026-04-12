var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapPost("/convert", (RequestDto req) =>
{
    return Results.Text(req.Input.ToUpper());
});

app.Run();

public record RequestDto(string Input);
public partial class Program { }