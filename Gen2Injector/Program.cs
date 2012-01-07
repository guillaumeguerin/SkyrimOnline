using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;
using System.Diagnostics;
using System.Threading;

namespace Gen2Injector
{
    class Program
    {
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(UInt32 dwDesiredAccess, Int32 bInheritHandle, Int32 dwProcessId);

        [DllImport("kernel32.dll")]
        public static extern Int32 CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll")]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, string lpBuffer, UIntPtr nSize, out IntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        public static extern UIntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32")]
        public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, UIntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, out IntPtr lpThreadId);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern UInt32 WaitForSingleObject(IntPtr hHandle, UInt32 dwMilliseconds);

        [DllImport("kernel32.dll")]
        static extern bool GetExitCodeThread(IntPtr hThread, out IntPtr lpExitCode);

        [DllImport("kernel32", SetLastError = true)]
        static extern IntPtr LoadLibrary(string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool FreeLibrary(IntPtr hModule);
        static void Main(string[] args)
        {
            string dll = "Gen2Injection.dll";
            Process process = Process.GetProcessesByName("tesv")[0];
            IntPtr bytesout;
            if (File.Exists(dll))
            {
                var hLoader = LoadLibrary(dll);
                var hLoaderProc = GetProcAddress(hLoader, "Loader");
                var moduleOffset = ((uint)hLoaderProc - (uint)hLoader);
                FreeLibrary(hLoader);
                Int32 bufferSize = dll.Length + 1;
                IntPtr hProcess = OpenProcess(0x1F0FFF, 1, process.Id);
                IntPtr AllocMem = VirtualAllocEx(hProcess, IntPtr.Zero, (uint)bufferSize, 0x1000, 0x04);
                WriteProcessMemory(hProcess, AllocMem, dll, (UIntPtr)bufferSize, out bytesout);
                UIntPtr Injector = (UIntPtr)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
                IntPtr hThread = (IntPtr)CreateRemoteThread(hProcess, (IntPtr)null, 0, Injector, AllocMem, 0, out bytesout);
                WaitForSingleObject(hThread, 5000);
                IntPtr hModule;
                GetExitCodeThread(hThread, out hModule);
                CloseHandle(hThread);
                IntPtr AllocMem2 = VirtualAllocEx(hProcess, IntPtr.Zero, 1, 0x1000, 0x04);
                IntPtr hThread2 = (IntPtr)CreateRemoteThread(hProcess, IntPtr.Zero, 0, (UIntPtr)((uint)hModule + moduleOffset), IntPtr.Zero, 0, out bytesout);
                UInt32 i = WaitForSingleObject(hThread, 5000);
                CloseHandle(hThread2);
                var m = process.Modules;
            }
        }
    }
}
