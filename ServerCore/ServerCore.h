#pragma once

#include <utility>
#include <string>
#include <iosfwd>
#include <vector>

using trackTimeByKart = std::pair<int, double>;

class ServerCore
{
public:
	ServerCore();
	~ServerCore() = default;

	void Listen();
	trackTimeByKart EvaluateRaceSummary(std::string filePath);

protected:
	std::vector<trackTimeByKart> ExtractInfoFromFile(std::ifstream& stream);
	trackTimeByKart GetBestLap(const std::vector<trackTimeByKart>& laps);
};
