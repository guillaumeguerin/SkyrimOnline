#pragma once
#include "stdafx.h"
#include <string>
class sPipe
{
public:
	sPipe(std::string Name);

	HANDLE Handle();
	bool Connect();
};