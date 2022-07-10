#include "pch4client.h"
#include "Race.h"
#include <chrono>
#include <format>
#include <string_view>
#include <time.h>
#include <cassert>
#include <fstream>

void Race::StartRace() {
	// race starts and data flows from the sensors async
	lapTimes.clear();

	SimulateRace();
}

void Race::SimulateRace() {
	// make async later
	using Time = std::chrono::system_clock;
	// for simulation purposes: lap time ~ 43 sec
	int lapTime = 43;
	for (int lap = 0; lap <= lapLimit; lap++) {
		for (auto& kart : kartNumbers) {
			auto passTime = std::chrono::system_clock::to_time_t(Time::now());
			tm now;
			localtime_s(&now, &passTime);
			AddToTime(now, lap * lapTime + std::rand() % 10 - 5);
			std::string nowStr = std::format("{}:{}:{}", now.tm_hour, now.tm_min, now.tm_sec);
			lapTimes.emplace_back(kart, nowStr);
		}
	}
}

void Race::AddToTime(tm& now, int seconds) {
	now.tm_sec += seconds;
	for (; 60 <= now.tm_sec;) {
		now.tm_min++; now.tm_sec -= 60;
	}
	for (; 60 <= now.tm_min;) {
		now.tm_hour++; now.tm_min -= 60;
	}
	for (; 24 <= now.tm_hour;) {
		now.tm_hour -= 24;	//ignore day increment
	}
}

void Race::WriteSummaryToFile(std::string fileName) {
	assert(!lapTimes.empty());
	std::ofstream outputFile(fileName);
	for (const auto& lapTime : lapTimes) {
		outputFile << lapTime.first << "," << lapTime.second << "\n";
	}
	outputFile.close();
}