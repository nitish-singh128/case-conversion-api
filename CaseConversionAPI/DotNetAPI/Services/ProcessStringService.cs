using System;
using System.Runtime.InteropServices;

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