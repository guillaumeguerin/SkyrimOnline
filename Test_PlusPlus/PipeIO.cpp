#include "PipeIO.h"
#include "stdafx.h"
#include "sPipe.h"
HANDLE __hpipehandle;

PipeIO::PipeIO(HANDLE PipeHandle)
{
	__hpipehandle = PipeHandle;
}

PipeIO::PipeIO(sPipe Pipe)
{
	__hpipehandle = Pipe.Handle();
}
PipeIO::PipeIO(string Name)
{
	string b("\\\\.\\pipe\\");
	b = b.append(Name);
	__hpipehandle = CreateNamedPipeA(b.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, PIPE_UNLIMITED_INSTANCES, 4096, 4096, PIPE_NOWAIT, NULL);
	ConnectNamedPipe(__hpipehandle, NULL);
}

byte PipeIO::ReadHeader()
{
	byte buffer[1];
	DWORD r;
	ReadFile(__hpipehandle, buffer, 1, &r, NULL);
	return buffer[0];
}

string PipeIO::ReadString()
{
	byte* buffer = new byte[2];
	DWORD r;
	ReadFile(__hpipehandle, buffer, 2, &r, NULL);
	short l = 0;
	buffer = new byte[l];
	ReadFile(__hpipehandle, buffer, l, &r, NULL);
	char* chars = (char*)buffer;
	return string(chars);
}

PipeIO::~PipeIO(void)
{
}
