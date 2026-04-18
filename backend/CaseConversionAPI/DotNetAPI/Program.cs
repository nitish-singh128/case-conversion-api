/**************************************************************************************************
 * File         : Program.cs
 *
 * Copyright    : (c) 2016–2026 nitishhsinghh. All rights reserved.
 * This material may be reproduced for teaching and learning purposes only.
 * It is not to be used in industry or for commercial purposes.
 *
 * Description  : Application entry point for the Word Case REST API.
 * Configures ASP.NET Core middleware pipeline, dependency injection,
 * CORS policies, OpenTelemetry observability, and Swagger.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date           Author           Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11     Nitish Singh     Initial implementation of application bootstrap
 * 1.1         2026-04-16     Nitish Singh     Optimized DI lifetime and refined CORS handling.
 * 1.2         2026-04-18     Nitish Singh     Integrated OpenTelemetry (OTLP) for distributed 
 * tracing across the native ABI boundary. Corrected OTLP namespace.
 **************************************************************************************************/

using Microsoft.OpenApi.Models;
using StringConversionAPI.Services;
using OpenTelemetry.Resources;
using OpenTelemetry.Trace;
using OpenTelemetry.Exporter; // Added to resolve OtlpExportProtocol

var builder = WebApplication.CreateBuilder(args);

// --- 1. OpenTelemetry & Observability ---
const string serviceName = "CaseConversion-Gateway";

builder.Services.AddOpenTelemetry()
    .ConfigureResource(resource => resource.AddService(serviceName))
    .WithTracing(tracing => tracing
        .AddSource("CaseConversion.Engine") 
        .AddAspNetCoreInstrumentation()      
        .AddHttpClientInstrumentation()      
        .AddOtlpExporter(options =>
        {
            options.Endpoint = new Uri("http://localhost:4317");
            // Corrected Enum Path: Removed the middle 'OpenTelemetryProtocol'
            options.Protocol = OtlpExportProtocol.Grpc; 
        }));

// --- 2. Controller & Documentation Services ---
builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c =>
{
    c.SwaggerDoc("v1", new OpenApiInfo { Title = "Word Case API", Version = "v1" });
});

// --- 3. Optimized CORS Policy ---
builder.Services.AddCors(options =>
{
    options.AddDefaultPolicy(policy =>
    {
        policy.AllowAnyOrigin()
              .AllowAnyHeader()
              .AllowAnyMethod()
              .SetPreflightMaxAge(TimeSpan.FromMinutes(10)); 
    });
});

// --- 4. Core Business Services ---
builder.Services.AddSingleton<ProcessStringService>();

var app = builder.Build();

// --- Middleware Pipeline ---
app.UseCors(); 

app.UseSwagger();
app.UseSwaggerUI(c =>
{
    c.SwaggerEndpoint("/swagger/v1/swagger.json", "Word Case API v1");
    c.RoutePrefix = string.Empty; 
});

app.UseAuthorization();
app.MapControllers();

if (app.Environment.EnvironmentName != "Testing")
{
    app.Run();
}

public partial class Program { }