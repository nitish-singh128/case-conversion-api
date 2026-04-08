using Microsoft.OpenApi.Models;
using StringConversionAPI.Services;

var builder = WebApplication.CreateBuilder(args);

// Add services
builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c =>
{
    c.SwaggerDoc("v1", new OpenApiInfo
    {
        Title = "Word Case API",
        Version = "v1",
        Description = "REST API for string case conversions"
    });
});

// CORS
builder.Services.AddCors(options =>
{
    options.AddDefaultPolicy(policy =>
    {
        policy.AllowAnyOrigin()
              .AllowAnyHeader()
              .AllowAnyMethod();
    });
});

builder.Services.AddScoped<ProcessStringService>();

var app = builder.Build();

// CORS
app.UseCors();

// Swagger
app.UseSwagger();
app.UseSwaggerUI(c =>
{
    c.SwaggerEndpoint("/swagger/v1/swagger.json", "Word Case API v1");
    c.RoutePrefix = string.Empty; // Swagger at root /
});

// Optional: comment out HTTPS redirection for dev
// app.UseHttpsRedirection();

app.UseAuthorization();
app.MapControllers();

app.Run();