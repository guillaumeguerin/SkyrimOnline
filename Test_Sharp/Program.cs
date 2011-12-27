using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet;
using System.Diagnostics;
using System.IO;
using System.Threading;
using SkyNet.Extension;

namespace Test_Sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            //Testing the plumbing
//             globals.MainPipe.WriteCommand(globals.commands.Note, "OMFGLULZMSG!");
//             Stopwatch w = new Stopwatch();
//             w.Start();
//             //Return an IntPtr valued with the byte system n = (n+1)^3 
//             //             byte[] ints = new byte[5];
//             //             for (byte i = 1; i < 5; i++)
//             //                 ints[i] = (byte)(i * i * i);
//             //             int value = BitConverter.ToInt32(ints, 1);
//             //1075513345
//             IntPtr r = (IntPtr)globals.MainPipe.GetCallback("super", "tester");
// 
//             //Return a byte array of length [Parameter]
//             byte[] test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             test = (byte[])globals.MainPipe.GetCallback("dbg_salsa", short.MaxValue);
//             w.Stop();
            SuperAssembly 
                ass = new SuperAssembly();
            string 
                test4 = ass.Call<string>("Test_Sharp.TestClass.Test4", new[] { "XX" }),
                test3 = ass.Call<string>("Test_Sharp.TestClass.Test3");
        }
    }
    class TestClass
    {
        public void Test1()
        {
            Console.WriteLine("SPACE");
        }
        public void Test2(string X)
        {
            Console.WriteLine("SPACE:[0]", X);
        }
        public string Test3()
        {
            return "SPACE";
        }
        string Test4(string X)
        {
            return "SPACE:" + X;
        }
    }
}
