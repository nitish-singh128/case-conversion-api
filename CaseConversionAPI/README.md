## Run the .NET REST API

Follow these steps to build and run the ASP.NET Core API.

### 1. Navigate to API project

```bash
cd CaseConversionAPI/DotNetAPI
```

### 2. Restore dependencies

```bash
dotnet restore
```

### 3. Build the project

```bash
dotnet build
```

### 4. Run the application

```bash
dotnet run
```

You should see output similar to:

```
Now listening on: http://localhost:5000
Application started. Press Ctrl+C to shut down.
```

### 5. Open Swagger UI

Open your browser and go to:

```
http://localhost:5000/swagger
```

### 6. Test the API

Use the **POST** endpoint:

```
POST /api/WordCase/convert
```

Example request body:

```json
{
  "text": "Hello World",
  "choice": 1
}
```

Example response:

```
HeLlO WoRlD
```

### Notes

* Ensure `libProcessStringDLL.dylib` is copied to `bin/Debug/net8.0`
* The API dynamically loads the native C++ shared library at runtime
* Works on macOS, Linux, and Windows (with respective DLL/SO/DYLIB)
