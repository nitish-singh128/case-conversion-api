/*********************************************************************/
/* File: ProcessStringService.cs                                     */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ProcessStringService                                */
/*                                                                   */
/* Description - Service responsible for invoking native C++ string  */
/*               conversion logic via platform-specific shared       */
/*               libraries. Dynamically loads the appropriate        */
/*               library and calls exported function using           */
/*               delegates.                                          */
/*                                                                   */
/* Notes       - Uses P/Invoke with NativeLibrary                    */
/*               Supports Windows, Linux, and macOS                  */
/*               Delegates conversion based on choice parameter      */
/*                                                                   */
/* $Log: ProcessStringService.cs                                     */
/* 1.0  11-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

using System;
using System.Runtime.InteropServices;
using System.IO;

namespace StringConversionAPI.Services
{
    public class ProcessStringService
    {
        private delegate IntPtr ProcessStringDelegate(string input, int choice);
        private readonly ProcessStringDelegate processString;

        public ProcessStringService()
        {
            string dllName;

            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
                dllName = "ProcessStringDLL.dll";
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
                dllName = "libProcessStringDLL.so";
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
                dllName = "libProcessStringDLL.dylib";
            else
                throw new PlatformNotSupportedException();

            string fullPath = Path.Combine(AppContext.BaseDirectory, dllName);
            Console.WriteLine("Loading native library from: " + fullPath);

            IntPtr handle = NativeLibrary.Load(fullPath);
            IntPtr symbol = NativeLibrary.GetExport(handle, "processStringDLL");

            processString = Marshal.GetDelegateForFunctionPointer<ProcessStringDelegate>(symbol);
        }

        public string Convert(string input, int choice)
        {
            if (string.IsNullOrEmpty(input))
                return input;

            IntPtr ptr = processString(input, choice);

            if (ptr == IntPtr.Zero)
                return string.Empty;

            return Marshal.PtrToStringAnsi(ptr) ?? string.Empty;
        }
    }
}