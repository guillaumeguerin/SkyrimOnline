#include "sPipe.h"
#include "../stdafx.h"
using namespace std;
#pragma once
class PipeIO
{
public:
	PipeIO(HANDLE PipeHandle);
	PipeIO(sPipe Pipe);
	PipeIO(string Name);
	~PipeIO(void);
	byte ReadHeader();
	string ReadString();
};

