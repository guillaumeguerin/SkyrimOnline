using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Pipes;
using System.Diagnostics;
using System.Threading;
namespace SkyNet
{
    public class Pipe
    {
        NamedPipeClientStream/*NamedPipeServerStream*/ stream; 
        public /*NamedPipeServerStream GetStream*/NamedPipeClientStream GetStream
        {
            get
            {
                return stream;
            }
        }
        public Pipe(string Name)
        {
//             stream = new NamedPipeServerStream(Name);
//             stream.WaitForConnection();
            stream = new NamedPipeClientStream(".", Name, PipeDirection.InOut);
            stream.Connect();
        }
        public void WriteString(string MSG)
        {
            byte[]
                head = new byte[] { 5 },
                data = Encoding.ASCII.GetBytes(MSG),
                leng = BitConverter.GetBytes((short)data.Length);
            GetStream.Write(head, 0, 1);
            GetStream.Write(leng, 0, 2);
            GetStream.Write(data, 0, data.Length);
        }
        public void WriteCommand(string Command, object Parameter)
        {
            byte[]
                head = new byte[] { 6 },
                data = Encoding.ASCII.GetBytes(Command),
                leng = BitConverter.GetBytes((short)data.Length);
            GetStream.Write(head, 0, 1);
            GetStream.Write(leng, 0, 2);
            GetStream.Write(data, 0, data.Length);
            data = Encoding.ASCII.GetBytes(Parameter.ToString());
            leng = BitConverter.GetBytes((short)data.Length);
            GetStream.Write(leng, 0, 2);
            GetStream.Write(data, 0, data.Length);
        }
        public object GetCallback(string Command, object Parameter)
        {
            byte[]
                head = new byte[] { 7 },
                data = Encoding.ASCII.GetBytes(Command),
                leng = BitConverter.GetBytes((short)data.Length);
            GetStream.Write(head, 0, 1);
            GetStream.Write(leng, 0, 2);
            GetStream.Write(data, 0, data.Length);
            data = Encoding.ASCII.GetBytes(Parameter.ToString());
            leng = BitConverter.GetBytes((short)data.Length);
            GetStream.Write(leng, 0, 2);
            GetStream.Write(data, 0, data.Length);
            string guid = Guid.NewGuid().ToString();
            data = Encoding.ASCII.GetBytes(guid);
            leng = BitConverter.GetBytes((short)data.Length);
            GetStream.Write(leng, 0, 2);
            GetStream.Write(data, 0, data.Length);
            while (!globals.Callbacks.ContainsKey(guid))
                Thread.Sleep(10);
            object r = globals.Callbacks[guid];
            globals.Callbacks.Remove(guid);
            return r;
        }
        internal KeyValuePair<string, object> GetStringCallback()
        {
            short len;
            byte[] buffer = new byte[2];
            GetStream.Read(buffer, 0, 2);
            len = BitConverter.ToInt16(buffer, 0);
            buffer = new byte[len];
            GetStream.Read(buffer, 0, len);
            string key = Encoding.ASCII.GetString(buffer);

            buffer = new byte[2];
            GetStream.Read(buffer, 0, 2);
            len = BitConverter.ToInt16(buffer, 0);
            buffer = new byte[len];
            GetStream.Read(buffer, 0, len);
            return new KeyValuePair<string, object>(key, globals.ParseBuffer(buffer));
        }
    }
}
