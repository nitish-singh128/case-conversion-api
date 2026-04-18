/**************************************************************************************************
 * File         : ProcessStringService.cs
 *
 * Copyright    : (c) 2016–2026 nitishhsinghh. All rights reserved.
 * This material may be reproduced for teaching and learning purposes only.
 * It is not to be used in industry or for commercial purposes.
 *
 * Class        : ProcessStringService
 *
 * Description  : Managed service wrapper for the native C++ string conversion engine.
 * Handles platform-specific library loading, symbol resolution, and
 * interop execution using P/Invoke and NativeLibrary APIs.
 *
 * Notes        : - Implements IDisposable to ensure proper release of native resources.
 * - Uses "Callee-Allocates, Caller-Frees" pattern for safe memory handling.
 * - Bridges managed (.NET) and unmanaged (C++) execution layers with OTEL.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date           Author           Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11     Nitish Singh     Initial implementation of native interop layer
 * 1.1         2026-04-13     Nitish Singh     Added memory safety, freeString delegate, IDisposable
 * 1.2         2026-04-18     Nitish Singh     Added OpenTelemetry instrumentation and updated 
 * delegate for distributed tracing (traceId).
 **************************************************************************************************/

using System;
using System.Runtime.InteropServices;
using System.IO;
using System.Diagnostics;

namespace StringConversionAPI.Services
{
    /// <summary>
    /// Service to facilitate communication between .NET and the native C++ 
    /// conversion library with built-in observability.
    /// </summary>
    public class ProcessStringService : IDisposable
    {
        #region Native Delegates

        // Updated Version 1.2: Added traceId parameter to the delegate signature
        private delegate IntPtr ProcessStringDelegate(
            [MarshalAs(UnmanagedType.LPStr)] string input, 
            int choice, 
            [MarshalAs(UnmanagedType.LPStr)] string traceId);

        private delegate void FreeStringDelegate(IntPtr ptr);

        #endregion

        #region Private Members

        private readonly ProcessStringDelegate _processString;
        private readonly FreeStringDelegate _freeStringDelegate;
        private readonly IntPtr _libraryHandle;
        private bool _disposed = false;

        // OpenTelemetry Activity Source
        private static readonly ActivitySource _activitySource = new("CaseConversion.Engine");

        #endregion

        public ProcessStringService()
        {
            string dllName = RuntimeInformation.IsOSPlatform(OSPlatform.Windows) ? "ProcessStringDLL.dll" :
                             RuntimeInformation.IsOSPlatform(OSPlatform.Linux)   ? "libProcessStringDLL.so" :
                             RuntimeInformation.IsOSPlatform(OSPlatform.OSX)     ? "libProcessStringDLL.dylib" :
                             throw new PlatformNotSupportedException("Unsupported OS platform.");

            string fullPath = Path.Combine(AppContext.BaseDirectory, dllName);

            _libraryHandle = NativeLibrary.Load(fullPath);
            if (_libraryHandle == IntPtr.Zero)
                throw new DllNotFoundException($"Unable to load native library at: {fullPath}");
            
            IntPtr procAddr = NativeLibrary.GetExport(_libraryHandle, "processStringDLL");
            IntPtr freeProcAddr = NativeLibrary.GetExport(_libraryHandle, "freeString");

            _processString = Marshal.GetDelegateForFunctionPointer<ProcessStringDelegate>(procAddr);
            _freeStringDelegate = Marshal.GetDelegateForFunctionPointer<FreeStringDelegate>(freeProcAddr);   
        }

        /// <summary>
        /// Converts the input string via native engine while capturing telemetry spans.
        /// </summary>
        public string Convert(string input, int choice)
        {
            if (string.IsNullOrEmpty(input))
                return input;

            // Start OpenTelemetry Span
            using var activity = _activitySource.StartActivity("Native-C++-Process", ActivityKind.Internal);
            
            // Generate the W3C Trace Context to pass to C++
            string traceId = activity?.Id ?? "no-trace-context";
            
            activity?.SetTag("conversion.choice", choice);
            activity?.SetTag("input.length", input.Length);

            IntPtr resultPtr = IntPtr.Zero;

            try
            {
                // Dispatch call to C++ with TraceContext
                resultPtr = _processString(input, choice, traceId);
                
                if (resultPtr == IntPtr.Zero)
                    return string.Empty;

                string result = Marshal.PtrToStringAnsi(resultPtr) ?? string.Empty;

                // Sentinel Check for security gate
                if (result == "ERROR_BUFFER_OVERFLOW_LIMIT_5MB")
                {
                    activity?.SetStatus(ActivityStatusCode.Error, "Input exceeds 5MB limit.");
                    throw new ArgumentException("Payload exceeds the native engine's 5MB security limit.");
                }
                    
                return result;
            }
            catch (Exception ex)
            {
                activity?.SetStatus(ActivityStatusCode.Error, ex.Message);
                throw;
            }
            finally
            {
                if (resultPtr != IntPtr.Zero)
                {
                    _freeStringDelegate(resultPtr);
                }
            }
        }

        #region Disposal Pattern

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (_libraryHandle != IntPtr.Zero)
                {
                    NativeLibrary.Free(_libraryHandle);
                }
                _disposed = true;
            }
        }

        ~ProcessStringService()
        {
            Dispose(false);
        }

        #endregion
    }
}