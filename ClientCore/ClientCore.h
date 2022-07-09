#pragma once
#include <vector>
#include <string>

class ClientCore
{
public:
	ClientCore();
	~ClientCore() = default;
	
	void AddKart(int kartNumber);
	std::string RetrieveBestLap();
	std::string RetrieveBestKart();

private:
	std::vector<int> karts;
};