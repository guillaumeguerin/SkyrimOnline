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
}