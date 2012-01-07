using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using SkyNet.SkyrimOnline.Game;

namespace SkyNet.SkyrimOnline.Network
{
    public partial class Session
    {
        public delegate void Callback(Packet P);

        Callback[] handlers = new Callback[Packet.Opcode.op_max];
        Callback[] handlersQuery = new Callback[1];

        Packet _inbound;
        internal readonly Server _host;
        internal readonly TcpClient _client;

        public Session(TcpClient Client, Server Host)
        {
            _client = Client;
            _host = Host;

            handlers[Packet.Opcode.CMSG_POSITION_LOOK] = HandlePositionAndLook;
            handlers[Packet.Opcode.CMSG_CHARACTER_INFO] = HandleCharacterInfo;
            handlers[Packet.Opcode.CMSG_CHAT] = HandleChatMessage;
            handlers[Packet.Opcode.CMSG_MOUNT_SPAWN] = HandleMount;
            handlers[Packet.Opcode.CMSG_MOUNT_REMOVE] = HandleUnmount;

            handlers[Packet.Opcode.CMSG_SHARD_PICK] = HandleShardPick;
            handlers[Packet.Opcode.CMSG_AUTHENTICATION] = HandleAuth;

            handlersQuery[Packet.Opcode.LOAD_USER] = HandleUserLoad;
        }
        public void Run()
        {

        }
        public void Start()
        {

        }
        public void Add(Session S)
        {

        }
        public void SetWorld(World World)
        {

        }
        public void Write(Packet Packet)
        {
            
        }
        public void Close()
        {
            _client.Close();
        }
        internal void HandlePositionAndLook(Packet P)
        {

        }
        internal void HandleCharacterInfo(Packet P)
        {

        }
        internal void HandleChatMessage(Packet P)
        {

        }
        internal void HandleMount(Packet P)
        {

        }
        internal void HandleUnmount(Packet P)
        {

        }
        internal void HandleShardPick(Packet P)
        {

        }
        internal void HandleUserLoad(Packet P)
        {

        }
        internal void HandlePlayerEvent(Session S)
        {

        }
    }
}
