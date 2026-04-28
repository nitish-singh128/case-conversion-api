## Reporting a Vulnerability

We take the security of our native interop layer and web gateway seriously. If you find a vulnerability, please follow these steps:

- Do not open a public issue. Please email the maintainer directly at <me.singhnitish@yandex.com>.

- Details to include: Provide a brief description of the vulnerability, the environment (e.g., Apple M2, Docker, Windows), and a Proof of Concept (PoC) if possible.

- Response Timeline: You can expect an acknowledgment within 24-48 hours. We aim to provide a full assessment and a resolution plan within 7 business days.

## Security Architecture & Hardening

This project implements several native-level security controls:

- Static Analysis: Every PR is subjected to a CodeQL audit to detect C++ memory leaks and C# injection vulnerabilities.

- ABI Guardrails: The native engine enforces a 5MB per-request buffer limit to prevent heap-based buffer overflow attacks.

- Memory Isolation: Every conversion request is stateless and reentrant, ensuring no cross-request data contamination in the unmanaged heap.
