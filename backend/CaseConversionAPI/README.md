# .NET 8 API Gateway: Native Interop Service

This module serves as the managed gateway for the Case Conversion ecosystem. It provides a robust, thread-safe ASP.NET Core REST API that orchestrates communication with the high-performance C++ native engine via Dynamic P/Invoke.

## Architectural Overview

The .NET layer is designed as a stateless "Thin Wrapper" around the native binary. It handles the critical bridge between Managed (System.String) and Unmanaged (char*) memory.

## Key Design Patterns

- Callee-Allocates / Caller-Frees: Implements an explicit memory ownership contract. The .NET layer invokes the native freeString export immediately after string marshalling to ensure a Zero-Leak heap profile.

- Dynamic DLL Loading: Uses System.Runtime.InteropServices.NativeLibrary for platform-agnostic symbol resolution (Windows .dll, Linux .so, macOS .dylib).

- Dependency Injection (DI): Registered as a Scoped or Singleton service to manage the lifecycle of the native library handle.

- Hardened Guardrails: Integrates with the native engine's 2MB buffer limit to prevent Heap Exhaustion or DoS attacks.

## Getting Started

### Prerequisites

- .NET 8.0 SDK

- Compiled C++ Shared Library (libProcessStringDLL) present in the project root or build output.

1. Automated Execution

Use the provided shell script to handle the entire lifecycle (Restore → Build → Publish → Run).

```Bash
chmod +x run-dotnet.sh
./run-dotnet.sh
```

2. Manual Development Workflow

```Bash
# Navigate to project
cd CaseConversionAPI/DotNetAPI

# Restore and Build
dotnet restore
dotnet build -c Release

# Execute
dotnet run --project DotNetAPI.csproj
```

## Testing Infrastructure

The project includes an extensive Integration Test Suite using Microsoft.AspNetCore.Mvc.Testing. This validates the full request-to-native-execution pipeline.

### Test Categories

- Basic: Core case transformations (Upper, Lower, Reverse).

- Advanced: Complex logic (SnakeCase, LeetSpeak, InvertWords).

- Edge Cases: Boundary validation for empty strings and whitespace.

- Contractual Safety: Validation of out-of-range choices and large input handling.

```Bash
# Run the xUnit suite
dotnet test
```

## API Contract

POST /api/WordCase/convert

Request Body:

```Bash
{
  "text": "The quick brown fox",
  "choice": 11
}
```

Successful Response (200 OK):

```Bash
{
  "output": "the_quick_brown_fox",
  "processedAt": "2026-04-14T20:45:00Z"
}
```

## Security & Memory Governance

| Feature              | Implementation                    | Architectural Justification |
|---------------------|----------------------------------|-----------------------------|
| Memory Cleanup      | `IDisposable` & `freeString`     | Implements the "Callee-Allocates, Caller-Frees" contract. Ensures unmanaged heap memory is reclaimed immediately after marshalling, achieving a zero-leak profile. |
| ABI Safety          | `Marshal.PtrToStringAnsi`        | Performs a deep-copy of native memory into the managed garbage-collected (GC) heap. This decouples the .NET string lifecycle from the native buffer. |
| Boundary Protection | Strict O(n) Length Checks        | Enforces a 2MB security gate at the native entry point. Prevents heap exhaustion and buffer overflow attacks before memory is allocated for strategies. |
| Thread Safety       | Stateless Reentrancy             | The native engine is entirely stateless and stack-allocated, allowing the .NET ThreadPool to execute concurrent P/Invoke calls without mutex contention. |