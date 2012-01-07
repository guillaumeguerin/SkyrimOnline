using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;

namespace SkyNet.SkyrimOnline.Network
{
    public class Packet
    {

        //May look into Protocol Buffers for serialization
        //http://code.google.com/p/protobuf/
        //http://code.google.com/p/protosharp/

        List<uint> _intData = new List<uint>();
        List<float> _floatData = new List<float>();
        List<string> _string = new List<string>();
        internal ushort _opcode;

        internal struct Opcode
        {
            public const ushort
            CMSG_AUTHENTICATION = 0,
            CMSG_POSITION_LOOK = 1,
            CMSG_CHARACTER_INFO = 2,
            SMSG_PLAYER_COUNT = 3,
            SMSG_PLAYER_SPAWN = 4,
            SMSG_PLAYER_MOVE_LOOK = 5,
            SMSG_PLAYER_REMOVE = 6,
            SMSG_NEW_PLAYER = 7,
            CMSG_CHAT = 8,
            SMSG_CHAT = 9,
            CMSG_MAGIC = 10,
            SMSG_TIME_SYNC = 11,
            SMSG_SHARD_LIST = 12,
            CMSG_SHARD_PICK = 13,
            SMSG_SHARD_HANDSHAKE = 14,
            SMSG_WEATHER_SYNC = 15,
            SMSG_PLAYER_MOUNT_SPAWN = 16,
            SMSG_PLAYER_MOUNT_REMOVE = 17,
            CMSG_MOUNT_SPAWN = 18,
            CMSG_MOUNT_REMOVE = 19,
            op_max = 20,

            //Queries
            LOAD_USER = 0;
        };

        public uint Int(int Index)
        {
            return _intData[Index];
        }
        public float Float(int Index)
        {
            return _floatData[Index];
        }
        public string String(int Index)
        {
            return _string[Index];
        }
        public void Push(uint Item)
        {
            _intData.Add(Item);
        }
        public void Push(float Item)
        {
            _floatData.Add(Item);
        }
        public void Push(string Item)
        {
            _string.Add(Item);
        }
    }
}
