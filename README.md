# Case Conversion API

This project demonstrates a full-stack architecture where a native C++ string conversion engine is exposed through a .NET REST API and consumed by a modern frontend UI.

---

## Components

### 1. C++ Conversion Engine

- Implements multiple string conversion strategies (Alternating Case, Capitalize Words, Snake Case, etc.).
- Built as a shared library using **CMake**:
  - Windows → `ProcessString.dll`
  - macOS → `libProcessString.dylib`
  - Linux → `libProcessString.so`

### 2. .NET REST API Wrapper

- Uses **P/Invoke** to call the exported C++ DLL functions.
- Provides REST endpoints (e.g., `/api/WordCase/convert`) for frontend consumption.
- Built and published with `dotnet publish`.

### 3. Frontend UI (Vite + React/TypeScript)

- Provides a user interface to input text and select conversion type.
- Calls the .NET REST API endpoints to perform conversions.
- Built with `npm run build` → outputs static files in `dist/`.

---

## Build Pipeline

The project is designed to be built in sequence:

1.Build C++ DLL

```bash
mkdir -p CaseConversionAPI/CppLib/build
cd CaseConversionAPI/CppLib/build
cmake ..
cmake --build . --config Release

```

2.Build .NET API

```Bash
dotnet restore CaseConversionAPI/DotNetAPI
dotnet publish CaseConversionAPI/DotNetAPI -c Release -o ./publish
cp CaseConversionAPI/CppLib/build/libProcessString.* ./publish/
```

3.Build Frontend

```Bash
cd string-conversion-ui
npm install
npm run build
```

## C++ DLL Interop (ProcessStringDLL)

The project exposes a **C++ string conversion engine** to the .NET REST API using a DLL and P/Invoke.

## Purpose

`ProcessStringDLL.cpp` acts as a bridge between:

- C++ conversion logic
- C# service layer
- REST API controller

It dispatches user input to the appropriate conversion strategy using **Factory + Strategy pattern**.

### Exported Function

```cpp
extern "C" PROCESSSTRING_API const char* processStringDLL(const char* input, int choice);
```

### Parameters

- `input` → C-string input text
- `choice` → integer representing conversion type

### Returns

- Converted string (C-style pointer)
- Returns original input if invalid choice

### Supported Conversion Choices

| Choice | Conversion       |
| ------ | ---------------- |
| 1      | Alternating Case |
| 2      | Capitalize Words |
| 3      | Lower Case       |
| 4      | Upper Case       |
| 5      | Sentence Case    |
| 6      | Toggle Case      |
| 7      | Reverse          |
| 8      | Remove Vowels    |
| 9      | Remove Spaces    |
| 10     | Invert Words     |
| 11     | Snake Case       |
| 12     | Kebab Case       |
| 13     | Leet Speak       |

### Design Patterns Used

- Strategy Pattern
- Factory Pattern
- Client Dispatcher

### Flow

```Bash
REST API (C#)
     ↓
ProcessStringService (P/Invoke)
     ↓
processStringDLL (C++)
     ↓
Factory → Strategy → Client
     ↓
Converted String
```

### Build Output

The C++ project builds a shared library:

- Windows → `ProcessString.dll`
- macOS → `libProcessString.dylib`
- Linux → `libProcessString.so`

This library is loaded by the C# service using P/Invoke.

### Integration Layer (C#)

The .NET service calls the DLL:

```csharp
[DllImport("ProcessString")]
private static extern IntPtr processStringDLL(string input, int choice);
```

This enables the REST API to use native C++ performance-critical logic.

### Architecture Overview

```Bash
C++ Conversion Engine
        ↑
   DLL Export Layer
        ↑
C# P/Invoke Wrapper
        ↑
ProcessStringService
        ↑
WordCaseController
        ↑
REST API
```

## Architecture View

```Bash
                +---------------------+
                |   Frontend (React)  |
                |   Vite + TypeScript |
                +----------+----------+
                           |
                       REST API call
                           |
                +----------v----------+
                |   REST API (C#)     |
                |   WordCaseController|
                +----------+----------+
                           |
                       P/Invoke
                           |
                +----------v----------+
                |  ProcessStringDLL   |  <-- DLL wrapper
                +----------+----------+
                           |
                +----------v----------+
                |   Core C++ Logic    |
                | (Factory + Strategy)|
                +----------+----------+
                           |
         +-----------------+-----------------+
         |                                   |
+--------v--------+               +----------v--------+
|  main.cpp CLI   |               | Google Tests      |
|  Local testing  |               | Unit testing      |
+-----------------+               +-------------------+
         
```

## Tech Stack

- C++ (conversion logic, built with CMake)
- .NET 8 (REST API wrapper, P/Invoke)
- React + Vite + TypeScript (frontend UI)
- GitHub Actions (CI/CD pipeline)
- Azure App Service + GitHub Pages (deployment targets)
