#pragma once
class sPipe
{
private:
	sPipe(std::string Name, bool IsServer);
public:
	HANDLE Handle();
	bool Connect();
};