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
    public static bool Test(this object n, string Param)
    {
        return Param == "x";
    }

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
            case 1:
                {
                    //Byte array
                    byte[] array = new byte[Buffer.Length - 1];
                    Array.Copy(Buffer, 1, array, 0, Buffer.Length - 1);
                    return array;
                }
        }
        return null;
    }
    static Pipe
        mainPipe = new Pipe("Tester"),
        dataEventPipe = new Pipe("Tester.DataEvent");
    public static Pipe MainPipe
    {
        get { return mainPipe; }
    }
    static Pipe DataEventPipe
    {
        get { return dataEventPipe; }
    }
    static Thread DataEventReader = new Thread(() =>
    {
        KeyValuePair<string, object> _a;
        while (true)
        {
            _a = dataEventPipe.GetStringCallback();
            if (_a.Key == null)
                continue;
            globals.Callbacks.Add(_a.Key, _a.Value);
        }
    });
    //Handle static con/destructors
    private class man
    {
        public man()
        {
            DataEventReader.Start();
        }
        ~man()
        {
            DataEventReader.Abort();
        }
    }
    private static man __man;
    static globals()
    {
        __man = new man();
    }
}

namespace Values
{
    public static class Type_Entity
    {
        public const int 
            Base = 0,
            NPC = 1;
    }
    public static class Type_NPC
    {
        public const int
            Base = 0;
    }
}