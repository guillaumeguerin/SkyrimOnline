// Test_PlusPlus.cpp : Defines the entry point for the console application.
//
// 
#include "stdafx.h"
#import "SkyNet.tlb"  no_namespace named_guids
#include <windows.h>
#import <mscorlib.tlb> raw_interfaces_only
// #include "HipIO.h"
// #include <math.h>
// 
// DWORD WINAPI Thread_no_2( LPVOID lpParam )
// {
// 	return 0;
// }
// 
// string _getString(HANDLE pipe)
// {
// 	byte lenBuffer[2];
// 	short len;
// 	DWORD read = 0;
// 	byte headerBuffer[1];
// 	string msg;
// 	byte *stringBuffer = 0;
// 	ReadFile(pipe, lenBuffer, 2, &read, NULL);
// 	len = (short)(lenBuffer[1] << 8) | lenBuffer[0];
// 	stringBuffer = new byte[len];
// 	ReadFile(pipe, stringBuffer, len, &read, NULL);
// 	msg = "";
// 	//Fuck you, C++. I worked around your trickery! >:D
// 	for(int i=0;i<len;i++)
// 		msg.append(1, stringBuffer[i]);
// 	return msg;
// }
// void _sendString(HANDLE pipe, string MSG)
// {
// 	short len = MSG.length();
// 	byte buffer[2];
// 	buffer[0] = (byte)(len & 255);
// 	buffer[1] = (byte)(len >> 8);
// 	DWORD writ = 0;
// 	WriteFile(pipe, buffer, 2, &writ, NULL);
// 	WriteFile(pipe, MSG.c_str(), len, &writ, NULL);
// }
// int _tmain(int argc, _TCHAR* argv[])
// {
// // 	sPipe pipe = sPipe("Tester");
// // 	BOOL b = pipe.Connect();
// // 	PipeIO io = new PipeIO(pipe);
// 	HANDLE pipe = Hipolipolopigus_ComIO_MakePipe("Tester"),
// 		callbackPipe = Hipolipolopigus_ComIO_MakePipe("Tester.DataEvent");//CreateNamedPipe("\\\\.\\pipe\\Tester", PIPE_ACCESS_DUPLEX,
// // 		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
// // 		PIPE_UNLIMITED_INSTANCES,
// // 		4096,
// // 		4096,
// // 		0,
// // 		NULL);
// 	ConnectNamedPipe(pipe, NULL);
// 	byte headerBuffer[1];
// 	DWORD read = 0;
// 	while(1)
// 	{
// 		headerBuffer[0] = 255;
// 		ReadFile(pipe, headerBuffer, 1, &read, NULL);
// 		if(headerBuffer[0]==5)
// 		{
// 			string msg = _getString(pipe);
// 		}
// 		else if(headerBuffer[0] == 6)
// 		{
// 			//Command
// 			string c = _getString(pipe),
// 				p = _getString(pipe);
// 			call(c, p);
// 		}
// 		else if(headerBuffer[0] == 7)
// 		{
// 			//Callback
// 			string c = _getString(pipe),
// 				p = _getString(pipe),
// 				guid = _getString(pipe);
// //  			int i = c.compare("super"),
// //  				i2 = p.compare("tester");
// 			if(c == "super" && p == "tester")
// 			{
// 				byte magicBuffer[5];
// 				magicBuffer[0] = 0;
// 				for(int v=1;v<5;v++)
// 					magicBuffer[v] = v*v*v;
// 				DWORD writ;
// 				byte magicLength[2];
// 				magicLength[0]=5;
// 				magicLength[1]=0;
// 				_sendString(callbackPipe, guid);
// 				WriteFile(callbackPipe, magicLength, 2, &writ, NULL);
// 				WriteFile(callbackPipe, magicBuffer, 5, &writ, NULL);
// 			}
// 			else if(c == "dbg_salsa")
// 			{
// 				short v = (short)atoi(p.c_str());
// 				byte *_Arr = new byte[v];
// 				_Arr[0] = 1;
// 				byte mbuff[2];
// 				mbuff[1] = (byte)(v >> 8);
// 				mbuff[0] = (byte)(v & 255);
// 				DWORD writ = 0;
// 				_sendString(callbackPipe, guid);
// 				WriteFile(callbackPipe, mbuff, 2, &writ, NULL);
// 				WriteFile(callbackPipe, _Arr, v, &writ, NULL);
// 				_Arr = NULL;
// 			}
// 			else if (c== "GetPosition")
// 			{
// 
// 			}
// 			p =  c = "";
// 		}
// 	}
// 	return 0;
// }
// 

int _tmain(int argc, _TCHAR* argv[])
{
	BaseEntity *cpi(0);
	
	return 0;
}