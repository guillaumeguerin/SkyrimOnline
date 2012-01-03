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
    public enum Type_Entity : byte
    {
        Base = 0,
        NPC = 1
    }
    public enum Type_NPC : byte
    {
        Base = 0
    }
    public enum Type_Item : byte
    {
        Base = 0
    }
}