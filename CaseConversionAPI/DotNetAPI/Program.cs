using StringConversionAPI.Services;

var builder = WebApplication.CreateBuilder(args);

// Register your service
builder.Services.AddSingleton<ProcessStringService>();

builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Enable Swagger if needed
app.UseSwagger();
app.UseSwaggerUI();

app.MapControllers();

app.Run();