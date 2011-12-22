#pragma once
class sPipe
{
	HANDLE _handle;
private:
	sPipe(std::string Name, bool IsServer);
public:
	HANDLE Handle()
	{
		return _handle;
	}
}