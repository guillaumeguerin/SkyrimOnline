#pragma once
#include "stdafx.h"
#define Hipolipolopigus_ComIO_MSG "msg"
#define Hipolipolopigus_ComIO_Console "ding"
HANDLE Hipolipolopigus_ComIO_MakePipe(const char* Name)
{
	string s = string("\\\\.\\pipe\\").append(Name);
	return CreateNamedPipeA(s.c_str(), PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,
		4096,
		4096,
		0,
		NULL);
}
#define Hipolipolopigus_ThreadMake(Method) CreateThread(NULL, NULL, Method, NULL, NULL, NULL)
#define Hipolipolopigus_ThreadMake2(Method, Param) CreateThread(NULL, NULL, Method, Param, NULL, NULL)
void ShowMSG(string Param)
{
	MessageBox(NULL, TEXT(Param.c_str()), "", 0);
}
void Console(string Param)
{
	printf(Param.c_str());
}
#ifndef PrintNote
#define Hipolipolopigus_ComIO_Note "note"
void _Note(string Note)
{
	Console(((string("Note: "))).append(Note.c_str()));
}
#endif
struct
{
	(void)(*fn)(string Param);
	const char* key;
}methodTable[] =
{
	{ &ShowMSG,		Hipolipolopigus_ComIO_MSG },
	{ &Console,		Hipolipolopigus_ComIO_Console },
	//Define __PrintNote when ScriptDragon is present
	#ifndef __PrintNote
	{ &_Note,		Hipolipolopigus_ComIO_Note},
	#else
	{
		&PrintNote,	Hipolipolopigus_ComIO_Note
	},
	#endif
	{ NULL,			NULL }
};

bool call( const string& name, string Param )
{
	for (int i = 0; methodTable[ i ].fn; i++)
		if (name == methodTable[ i ].key)
		{
			(*(methodTable[ i ].fn))(Param);
			return true;
		}
		return false;
}