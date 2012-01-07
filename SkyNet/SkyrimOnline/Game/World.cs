using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet.SkyrimOnline.Network;
using System.Threading;
using Timer = SkyNet.Math.Timer;
using SkyNet.SkyrimOnline.System;

namespace SkyNet.SkyrimOnline.Game
{
    public partial class World : Job
    {
        internal bool _persistent;
        internal string _name;
        internal Queue<Session> _sessions = new Queue<Session>();
        /*internal Mutex _guard, _releaseGuard;*/               //Possibly not necessary given the nature of C#
        internal Timer _timer;
        internal bool _scheduled;

        internal Server _server;

        internal TimeManager _timeManager;
        internal WeatherManager _weatherManager;

        public World(string Name, bool Persistent, Server Server)
        {
            _persistent = Persistent;
            _name = Name;
            _server = Server;
        }

        public uint Count;
        public string Name
        {
            get { return _name; }
        }
        public bool IsMarkedForDelete;      //Purge sounds cooler :3

        public void Work()
        {
            float elapsed = _timer.ElapsedAndRestart;
            if (_sessions.Count > 0)
            {
                _timeManager.Update(elapsed);
                lock (_sessions)
                {
                    int l = _sessions.Count,
                        i = 0;
                    for (; i < l; i++)
                        _sessions.ElementAt(i).Run();
                }
            }
            else if (elapsed > 120)
            {
                _scheduled = false;
                return;
            }
            _server._queue.Enqueue(this);
            Thread.Sleep(0);
        }

        public void Start()
        {

        }

        public void Add(Session Player)
        {
            lock (_sessions)
            {
                _sessions.Enqueue(Player);
            }
            Player.SetWorld(this);
            Packet packet = new Packet()
            {
                _opcode = Packet.Opcode.SMSG_SHARD_HANDSHAKE
            };
            packet.Push((uint)1);
            Player.Write(packet);

            SendTimeSync(Player);
            SendWeatherSync(Player);
        }
        void Remove(Session Player)
        {
            lock (_sessions)
            {
                // ♥ LINQ
                _sessions = new Queue<Session>(
                    from s in _sessions
                    where s._client.Client.RemoteEndPoint != Player._client.Client.RemoteEndPoint
                    select s);
            }
        }

        void DispatchPlayerMoveAndLook(Session pPlayer)
        {
            lock (_sessions)
            {
                foreach (Session s in _sessions)
                    if (s != pPlayer)
                        s.HandlePlayerEvent(pPlayer);
            }
        }
        void DispatchToAll(Packet Packet)
        {

        }
        void DispatchToAllButMe(Packet Packet, Session Player)
        {

        }
    }
}
