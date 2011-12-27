#include						"stdafx.h"
#include						"sPipe.h"
#include						<string.h>
#include						<tchar.h>
#pragma once
using namespace					std;

HANDLE __pipehandle;
//"\\\\.\\pipe\\"
sPipe::sPipe(string Name)
{
	string _name("\\\\.\\pipe\\");
	_name = _name.append(Name);
	__pipehandle = CreateNamedPipeA(_name.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 4096, 4096, PIPE_WAIT, NULL);
}
bool sPipe::Connect()
{
	return ConnectNamedPipe(__pipehandle, NULL);
}
HANDLE sPipe::Handle()
{
	return __pipehandle;
}