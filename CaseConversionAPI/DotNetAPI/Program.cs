/*********************************************************************/
/* File: Program.cs                                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Application entry point configuring ASP.NET Core    */
/*               pipeline, dependency injection, CORS, and Swagger   */
/*               for the Word Case REST API. Registers services and  */
/*               maps controller endpoints.                          */
/*                                                                   */
/* Notes       - Enables Swagger UI at root                          */
/*               Configures CORS for cross-origin requests           */
/*               Registers ProcessStringService for DI               */
/*                                                                   */
/* $Log: Program.cs                                                  */
/* 1.0  11-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

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