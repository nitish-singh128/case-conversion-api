/**************************************************************************************************
 * File        : ProcessStringService.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : ProcessStringService
 *
 * Description : Managed service wrapper for the native C++ string conversion engine.
 *               Handles platform-specific library loading, symbol resolution, and
 *               interop execution using P/Invoke and NativeLibrary APIs.
 *
 * Notes       : - Implements IDisposable to ensure proper release of native resources.
 *               - Uses "Callee-Allocates, Caller-Frees" pattern for safe memory handling.
 *               - Performs runtime OS detection to load appropriate shared library.
 *               - Bridges managed (.NET) and unmanaged (C++) execution layers.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11  Nitish Singh    Initial implementation of native interop layer
 * 1.1         2026-04-13  Nitish Singh    Added memory safety, freeString delegate, IDisposable
 *
 **************************************************************************************************/

using System;
using System.Runtime.InteropServices;
using System.IO;

namespace StringConversionAPI.Services
{
    /// <summary>
    /// Service to facilitate communication between .NET and the native C++ 
    /// conversion library.
    /// </summary>
    public class ProcessStringService : IDisposable
    {
        #region Native Delegates

        private delegate IntPtr ProcessStringDelegate([MarshalAs(UnmanagedType.LPStr)] string input, int choice);
        private delegate void FreeStringDelegate(IntPtr ptr);

        #endregion

        #region Private Members

        private readonly ProcessStringDelegate _processString;
        private readonly FreeStringDelegate _freeStringDelegate;
        private readonly IntPtr _libraryHandle;
        private bool _disposed = false;

        #endregion

        /// <summary>
        /// Initializes the service by dynamically loading the platform-specific 
        /// native library and mapping required function exports.
        /// </summary>
        public ProcessStringService()
        {
            string dllName = RuntimeInformation.IsOSPlatform(OSPlatform.Windows) ? "ProcessStringDLL.dll" :
                             RuntimeInformation.IsOSPlatform(OSPlatform.Linux)   ? "libProcessStringDLL.so" :
                             RuntimeInformation.IsOSPlatform(OSPlatform.OSX)     ? "libProcessStringDLL.dylib" :
                             throw new PlatformNotSupportedException("Unsupported OS platform.");

            string fullPath = Path.Combine(AppContext.BaseDirectory, dllName);

            // 1. Load the native library
            _libraryHandle = NativeLibrary.Load(fullPath);
            if (_libraryHandle == IntPtr.Zero)
                throw new DllNotFoundException($"Unable to load native library at: {fullPath}");
            
            // 2. Resolve function pointers
            IntPtr procAddr = NativeLibrary.GetExport(_libraryHandle, "processStringDLL");
            IntPtr freeProcAddr = NativeLibrary.GetExport(_libraryHandle, "freeString");

            // 3. Map to managed delegates
            _processString = Marshal.GetDelegateForFunctionPointer<ProcessStringDelegate>(procAddr);
            _freeStringDelegate = Marshal.GetDelegateForFunctionPointer<FreeStringDelegate>(freeProcAddr);   
        }

        /// <summary>
        /// Converts the input string using the specified strategy choice via 
        /// the native engine.
        /// </summary>
        public string Convert(string input, int choice)
        {
            if (string.IsNullOrEmpty(input))
                return input;

            IntPtr resultPtr = IntPtr.Zero;

            try
            {
                // Dispatch call to C++
                resultPtr = _processString(input, choice);
                
                if (resultPtr == IntPtr.Zero)
                    return string.Empty;

                // Marshal unmanaged C-string back to managed string (System.String)
                return Marshal.PtrToStringAnsi(resultPtr) ?? string.Empty;
            }
            finally
            {
                // CRITICAL: Call the native free() via our exported freeString function
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