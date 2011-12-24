using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet;
using System.Diagnostics;
using System.IO;
using System.Threading;

namespace Test_Sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            DataEventReader.Start();
            p.WriteCommand(globals.commands.Note, "OMFGLULZMSG!");
            object r = p.GetCallback("super", "tester");
            byte[] ints = new byte[5];
            for (byte i = 1; i < 5; i++)
                ints[i] = (byte)(i*i*i);
            int value = BitConverter.ToInt32(ints, 1);
        }
        static Pipe
            p = new Pipe("Tester"),
            dataEventPipe = new Pipe("Tester.DataEvent");
        static Thread DataEventReader = new Thread(()=>
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
    }
}
