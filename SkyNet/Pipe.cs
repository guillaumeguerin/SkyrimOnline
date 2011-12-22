using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Pipes;
namespace SkyNet
{
    public class Pipe
    {
        bool isServer;
        PipeStream stream;
        public bool IsServer
        {
            get { return isServer; }
        }
        public dynamic GetStream
        {
            get
            {
                if(isServer)
                    return (NamedPipeServerStream)stream;
                return (NamedPipeClientStream)stream;
            }
        }
        private Pipe(string Name, bool IsServer)
        {
            if (isServer = IsServer)
                stream = new NamedPipeServerStream(Name, PipeDirection.InOut);
            else
                stream = new NamedPipeClientStream(".", Name, PipeDirection.InOut);
        }

        //To make it simple on the front-end
        public static Pipe MakeListener(string Name)
        {
            return new Pipe(Name, true);
        }
        public static Pipe MakeClient(string Name)
        {
            return new Pipe(Name, false);
        }
    }
}
