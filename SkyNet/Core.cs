using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public static class Core
{
    public static object Call(string Command, object Parameter)
    {
        if (Parameter == null)
            Parameter = 0;
        return globals.MainPipe.GetCallback(Command, Parameter);
    }
}
