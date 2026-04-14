/**************************************************************************************************
 * File        : Startup.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : Startup
 *
 * Description : Configures application services and the HTTP request pipeline
 *               for the String Conversion REST API. Responsible for dependency
 *               injection setup, middleware registration, and endpoint mapping.
 *
 * Notes       : - Registers ProcessStringService for dependency injection.
 *               - Configures controllers and API endpoint discovery.
 *               - Enables Swagger UI in development environments.
 *               - Defines middleware pipeline including routing and authorization.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11  Nitish Singh    Initial implementation of startup configuration
 *
 **************************************************************************************************/

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