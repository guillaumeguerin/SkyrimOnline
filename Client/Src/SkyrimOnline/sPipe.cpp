#include "StdAfx.h"
#include "sPipe.h"


sPipe::sPipe(std::string Name, bool IsServer)
{
	Name.append(SkyNet_PipeStart);
}


sPipe::~sPipe(void)
{
}
