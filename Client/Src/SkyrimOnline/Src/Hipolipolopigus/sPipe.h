#pragma once
class sPipe
{
private:
	sPipe(std::string Name);
public:
	HANDLE Handle();
	bool Connect();
};