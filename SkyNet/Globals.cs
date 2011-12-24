using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using SkyNet;
using System.Threading;

//All SkyNet C# globals, class is lower-case to accelerate typing
public static class globals
{
    public static int Core_Check(string uParam)
    {
        Process[] p;
        return (p = Process.GetProcessesByName(Process.GetCurrentProcess().ProcessName)).Length == 1 ? 0 : p[1].Handle.ToInt32();
    }
    public static int Core_Main(string uParam)
    {
        Thread T = new Thread(() => Program.Main(null));
        T.Start();
        return 0;
    }

    public static class commands
    {
        public const string
            Message = "msg",
            Console = "ding",
            Note = "note";
    }

    public static Dictionary<string, object> Callbacks = new Dictionary<string, object>();

    public static object ParseBuffer(byte[] Buffer)
    {
        switch (Buffer[0])
        {
            case 0:
                {
                    //I32 Pointer
                    int i = BitConverter.ToInt32(Buffer, 1);
                    return new IntPtr(i);
                }
        }
        return null;
    }
}