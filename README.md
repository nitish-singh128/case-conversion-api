## C++ DLL Interop (ProcessStringDLL)

The project exposes a **C++ string conversion engine** to the .NET REST API using a DLL and P/Invoke.

### Purpose

`ProcessStringDLL.cpp` acts as a bridge between:

* C++ conversion logic
* C# service layer
* REST API controller

It dispatches user input to the appropriate conversion strategy using **Factory + Strategy pattern**.

### Exported Function

```cpp
extern "C" PROCESSSTRING_API const char* processStringDLL(const char* input, int choice);
```

### Parameters

* `input` → C-string input text
* `choice` → integer representing conversion type

### Returns

* Converted string (C-style pointer)
* Returns original input if invalid choice

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

* Strategy Pattern
* Factory Pattern
* Client Dispatcher

### Flow

```
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

* Windows → `ProcessString.dll`
* macOS → `libProcessString.dylib`
* Linux → `libProcessString.so`

This library is loaded by the C# service using P/Invoke.

### Integration Layer (C#)

The .NET service calls the DLL:

```csharp
[DllImport("ProcessString")]
private static extern IntPtr processStringDLL(string input, int choice);
```

This enables the REST API to use native C++ performance-critical logic.

### Architecture Overview

```
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
