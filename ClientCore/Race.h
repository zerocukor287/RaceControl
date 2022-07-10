#pragma once

#include <set>
#include <string>
#include <vector>
#include "RaceDefines.h"

class Race
{
public:
	Race(int laps, std::initializer_list<int> karts) : lapLimit(laps), kartNumbers(karts) { };
	~Race() = default;

	void StartRace();
	void SimulateRace();
	static void AddToTime(tm& now, int seconds);
	void WriteSummaryToFile(std::string fileName);

private:
	int lapLimit;
	std::set<int> kartNumbers;

	std::vector<passTimeByKart> lapTimes;
};