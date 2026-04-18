# Contributing to CaseConversionAPI

First off, thank you for considering contributing! This project is a high-performance polyglot system. To maintain the architectural integrity of the Native-to-Managed bridge, please follow these guidelines.

## Architectural Principles

Before submitting a Pull Request, ensure your changes adhere to these core tenets:

- Statelessness: The C++ engine must remain stateless and reentrant to ensure thread-safety within the .NET ThreadPool.

- ABI Stability: Any changes to the ProcessStringDLL interface must maintain C-linkage compatibility.

- Zero-Leak Policy: Every malloc or new in the native layer must have a documented lifecycle and a corresponding free or delete.

## Development Workflow

1. Native Layer (C++17)

Format: We use Clang-Format. Ensure your code matches the .clang-format specification.

Linting: Run Clang-Tidy to check for common C++ pitfalls.

Tests: New strategies must include a GoogleTest suite in tests/CppTests/.

```Bash
# Build and run native tests
cd backend/CaseConversionAPI/CppLib/build
cmake ..
make
./runTests
```

2. Managed Layer (.NET 8)

- Style: Follow standard C# coding conventions.

- Telemetry: If adding a new service, ensure it utilizes the ActivitySource named CaseConversion.Engine for trace propagation.

- Interop: Use SafeHandle or IntPtr with explicit cleanup for any new P/Invoke calls.

## Testing Requirements

We enforce a strict testing policy. No PR will be merged without:

1. Unit Tests: For all new conversion logic.

2. Integration Tests: xUnit tests in the .NET gateway ensuring the bridge is intact.

3. Telemetry Check: Verification that spans are correctly generated and the TraceID is propagated to the native engine.

## Pull Request Process

1. Branching: Create a feature branch from main (e.g., feat/new-strategy-name).

2. Documentation: Update DESIGN.md if you are changing the architectural flow.

3. Badges: Ensure the CI pipeline passes. We monitor:

    - C++ Core & GoogleTest
    - .NET API Integration
    - OpenTelemetry E2E Verification

4. Review: At least one maintainer must review the code for memory safety and ABI compliance.

## Security & Vulnerabilities

If you find a security hole (especially regarding buffer overflows in the native bridge), please do not open a public issue. Email the maintainer directly at [me.singhnitish@gmail.com] to ensure a coordinated disclosure.

## License

By contributing to this project, you agree that your contributions will be licensed under the Apache License, Version 2.0. You also grant a perpetual, worldwide, non-exclusive, no-charge, royalty-free, irrevocable patent license to any patent claims controllable by you that are infringed by your contribution.
