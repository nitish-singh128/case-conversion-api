/**************************************************************************************************
 * File        : Program.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Description : Application entry point for the Word Case REST API.
 *               Configures ASP.NET Core middleware pipeline, dependency injection,
 *               CORS policies, and API documentation via Swagger.
 *
 * Notes       : - Registers controllers and application services for DI.
 *               - Enables Swagger UI at root for API exploration.
 *               - Configures permissive CORS policy for cross-origin access.
 *               - Skips application run during integration testing.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11  Nitish Singh    Initial implementation of application bootstrap
 *
 **************************************************************************************************/

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

// Only run when NOT testing
if (app.Environment.EnvironmentName != "Testing")
{
    app.Run();
}

// Required for tests
public partial class Program { }