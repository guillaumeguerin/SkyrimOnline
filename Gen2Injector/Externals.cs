using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Gen2Injector
{
    public sealed class Externals
    {
        public sealed class System
        {
            public static UIntPtr GetLoadLibraryA
            {
                get
                {
                    return (UIntPtr)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
                }
            }
            [DllImport("kernel32.dll")]
            public static extern IntPtr OpenProcess(UInt32 dwDesiredAccess, Int32 bInheritHandle, Int32 dwProcessId);

            [DllImport("kernel32.dll")]
            public static extern Int32 CloseHandle(IntPtr hObject);

            [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
            public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

            [DllImport("kernel32.dll")]
            public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, string lpBuffer, UIntPtr nSize, out IntPtr lpNumberOfBytesWritten);

            [DllImport("kernel32.dll", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
            public static extern UIntPtr GetProcAddress(IntPtr hModule, string procName);

            [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
            public static extern IntPtr GetModuleHandle(string lpModuleName);

            [DllImport("kernel32")]
            public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, UIntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, out IntPtr lpThreadId);

            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern UInt32 WaitForSingleObject(IntPtr hHandle, UInt32 dwMilliseconds);

            [DllImport("kernel32.dll")]
            public static extern bool GetExitCodeThread(IntPtr hThread, out IntPtr lpExitCode);

            [DllImport("kernel32", SetLastError = true)]
            public static extern IntPtr LoadLibrary(string lpFileName);

            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool FreeLibrary(IntPtr hModule);
        }
        public sealed class ScriptDragon
        {
            [DllImport("Gen2Injection.dll")]
            public static extern uint GetCurrentPlayerID();
        }
    }
}
