#pragma once

#include <utility>
#include <string>

using trackTimeByKart = std::pair<int, double>;

class ServerCore
{
public:
	ServerCore();
	~ServerCore() = default;

	void Listen();
	trackTimeByKart EvaluateRaceSummary(std::string filePath);

private:
	trackTimeByKart bestLap;
};
