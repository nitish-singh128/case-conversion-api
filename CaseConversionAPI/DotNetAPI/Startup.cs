/*********************************************************************/
/* File: Startup.cs                                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       : Startup                                             */
/*                                                                   */
/* Description : Configures services and HTTP request pipeline       */
/*               for the String Conversion REST API. Registers       */
/*               application services, controllers, and Swagger.     */
/*                                                                   */
/* Notes       : Adds ProcessStringService as singleton and          */
/*               enables Swagger UI in development environment.      */
/*********************************************************************/

using StringConversionAPI.Services;

public class Startup
{
    public IConfiguration Configuration { get; }

    public Startup(IConfiguration configuration)
    {
        Configuration = configuration;
    }

    public void ConfigureServices(IServiceCollection services)
    {
        // Add services here
        services.AddSingleton<ProcessStringService>();
        services.AddControllers();
        services.AddEndpointsApiExplorer();
        services.AddSwaggerGen();
    }

    public void Configure(WebApplication app, IWebHostEnvironment env)
    {
        if (env.IsDevelopment())
        {
            app.UseSwagger();
            app.UseSwaggerUI();
        }

        app.UseRouting();
        app.UseAuthorization();
        app.MapControllers();
    }
}