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
    public static class commands
    {
        public const string
            Message = "msg",
            Console = "ding",
            Note = "note";
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