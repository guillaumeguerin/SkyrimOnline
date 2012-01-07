using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SkyNet.SkyrimOnline.Network;

namespace SkyNet.SkyrimOnline.Game
{
    public partial class World
    {
        internal void SendTimeSync(Session Player)
        {
            Packet p = new Packet()
            {
                _opcode = Packet.Opcode.SMSG_TIME_SYNC
            };
            p.Push(_timeManager.Hour);
            p.Push(_timeManager.Day);
            p.Push(_timeManager.Month);
            Player.Write(p);
        }
        internal void SendWeatherSync(Session Player)
        {
            Packet p = new Packet()
            {
                _opcode = Packet.Opcode.SMSG_WEATHER_SYNC
            };
            p.Push(_weatherManager.Current);
            Player.Write(p);
        }
    }
}
