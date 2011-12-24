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
            globals.MainPipe.WriteCommand(globals.commands.Note, "OMFGLULZMSG!");
            Stopwatch w = new Stopwatch();
            w.Start();
            //Return an IntPtr valued with the byte system n = (n+1)^3 
            //             byte[] ints = new byte[5];
            //             for (byte i = 1; i < 5; i++)
            //                 ints[i] = (byte)(i * i * i);
            //             int value = BitConverter.ToInt32(ints, 1);
            //1075513345
            IntPtr r = (IntPtr)globals.MainPipe.GetCallback("super", "tester");

            //Return a byte array of length [Parameter]
            byte[] test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
            w.Stop();
        }
    }
}
