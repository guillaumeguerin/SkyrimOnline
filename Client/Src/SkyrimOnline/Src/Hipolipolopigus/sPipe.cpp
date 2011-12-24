#include						"stdafx.h"
#include						"sPipe.h"
#include						<string.h>
#pragma once
using namespace					std;

HANDLE __hpipehandle;

sPipe::sPipe(string Name)
{
	string _name("\\.\\pipe\\");
	_name = _name.append(Name);
	__hpipehandle = CreateNamedPipe(_name.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 4096, 4096, PIPE_WAIT, NULL);
}
bool sPipe::Connect()
{
	return ConnectNamedPipe(__hpipehandle, NULL);
}
HANDLE sPipe::Handle()
{
	return __hpipehandle;
}