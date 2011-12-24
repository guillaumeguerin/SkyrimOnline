// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define							VC_EXTRALEAN

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <shlwapi.h>
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "sPipe.h"
#include "PipeIO.h"

std::wstring s2ws(std::string s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


// TODO: reference additional headers your program requires here
