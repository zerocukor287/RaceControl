#pragma once
#include <vector>
#include <string>
#include "Race.h"

class ClientCore
{
public:
	ClientCore();
	~ClientCore() = default;
	
	void AddKart(int kartNumber);
	void AddKart(std::initializer_list<int> kartNumbers);
	void SetLapNumber(int newLapNumber) noexcept { lapNumber = newLapNumber; };
	void StartNewRace();
	void NotifyServer(std::string content);
	std::string RetrieveBestLap();
	std::string RetrieveBestKart();

private:
	std::vector<Race> race;
	std::set<int> kartNumberBuffer;
	int lapNumber{3};
};