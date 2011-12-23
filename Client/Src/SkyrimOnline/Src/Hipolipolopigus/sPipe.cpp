#include						"stdafx.h"
#include						"sPipe.h"
#include						<string.h>
#pragma once
using namespace					std;

HANDLE _handle;

sPipe::sPipe(string Name, bool IsServer)
{
	string _name(SkyNet_PipeStart);
	_name = _name.append(Name);
	_handle = CreateNamedPipe(_name.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 4096, 4096, PIPE_WAIT, NULL);
}
bool sPipe::Connect()
{
	return ConnectNamedPipe(_handle, NULL);
}
HANDLE sPipe::Handle()
{
	return _handle;
}