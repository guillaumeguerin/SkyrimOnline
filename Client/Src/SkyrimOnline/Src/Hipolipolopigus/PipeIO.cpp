#include "PipeIO.h"

HANDLE _handle;

PipeIO::PipeIO(HANDLE PipeHandle)
{
	_handle = PipeHandle;
	Init();
}

PipeIO::PipeIO(sPipe Pipe)
{
	_handle = sPipe.Handle();
	Init();
}
PipeIO::PipeIO(string Name)
{
	sPipe p = sPipe(Name);
	_handle = p.Handle(;
	Init();
}

byte PipeIO::ReadHeader()
{
	byte* buffer = new byte[1];
	DWORD r;
	ReadFile(_handle, buffer, 1, &r, NULL);

	return buffer[0];
}

string PipeIO::ReadString()
{
	byte[] buffer = new byte[2];
	DWORD r;
	ReadFile(_handle, buffer, 2 &r, NULL);
	short l = 0;
	buffer = new byte[l];
	ReadFile(_handle, buffer, l, &r, NULL);
	char* chars = dynamic_cast<char*>(buffer);
	return string(chars);
}

void Init()
{

}

PipeIO::~PipeIO(void)
{
}
