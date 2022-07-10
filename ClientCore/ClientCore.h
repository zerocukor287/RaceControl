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
	void SetLapNumber(int newLapNumber) noexcept { lapNumber = newLapNumber; };
	void StartNewRace();
	std::string RetrieveBestLap();
	std::string RetrieveBestKart();

private:
	std::vector<Race> race;
	std::set<int> kartNumberBuffer;
	int lapNumber{3};
};