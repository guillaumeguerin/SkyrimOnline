using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using SkyNet.Extension;
using SkyNet.SkyrimOnline.System;
using SkyNet.SkyrimOnline.Game;

namespace SkyNet.SkyrimOnline.Network
{
    public class Server
    {
        internal class WorldManager : MasterObject<string,World>
        {

        }
        internal TcpListener _server;
        internal SuperAssembly _superAssembly;
        internal bool _running;
        internal WorkQueue _queue = new WorkQueue();
        internal WorldManager _worlds = new WorldManager();

        public Server(int Port)
        {
            _server = new TcpListener(IPAddress.Loopback ,Port);
        }
        public void Start()
        {
            (_superAssembly = new SuperAssembly()).LoadAll();
            _server.Start();
            _running = true;
        }
        /// <summary>
        /// Not sure if this is necessary
        /// ToDo:DBQueue
        /// </summary>
        public void Scale()
        {
            uint logic = (uint)API._this.ProcessorAffinity.ToInt32(),
                db = 1,
                core = 1;
            if (logic > 3)
                core = logic - (db = logic / 4);
            _queue = new WorkQueue(core);
        }
        public void Run()
        {

        }
        public void Stop()
        {
            _running = false;
            _server.Stop();
        }
        public void Remove(Session Session)
        {
           
        }
        public void AddShard(World World)
        {
            API.OnAddShard(this, World);
            _worlds[World._name] = World;
        }
    }
}
