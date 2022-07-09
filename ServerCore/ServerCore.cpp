// ServerCore.cpp : Defines the functions for the static library.
//

#include "pch4serverCore.h"

#include "ServerCore.h"

#include <iostream>
#include <fstream>
#include <sstream>

ServerCore::ServerCore() {

}

void ServerCore::Listen() {

}

static bool onlyNumeric(const std::string& str) {
	// returns true for numbers with .
	for (auto c : str) {
		if (!(c == '0' || c == '1' || c == '2' || c == '3' || c == '4'
			|| c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == ':'))
			return false;
	}
	return true;
}

static int countChars(const std::string& str, char c) {
	int count = 0;
	for (auto character : str) {
		if (c == character) count++;
	}
	return count;
}

static double convertToSeconds(const std::string& date) {
	double seconds = 0.0;
	std::string timeSegment;
	int numberOfTimeSegments = countChars(date, ':');
	std::stringstream stateStream(date);
	while (std::getline(stateStream, timeSegment, ':')) {
		seconds += std::stod(timeSegment) * std::pow(60, numberOfTimeSegments);
		numberOfTimeSegments--;
	}
	return seconds;
}

trackTimeByKart ServerCore::EvaluateRaceSummary(std::string filePath) {
	try {
		std::ifstream fileStream(filePath, std::ifstream::in);
		auto lapTimes = ExtractInfoFromFile(fileStream);
		fileStream.close();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	return {4, 54.321};
}

std::vector<trackTimeByKart> ServerCore::ExtractInfoFromFile(std::ifstream& stream) {
	std::vector<trackTimeByKart> lapTimes;
	std::string oneLine, buffer;
	while (std::getline(stream, oneLine, '\n')) {
		std::stringstream strStream(oneLine);
		std::string kart, date;

		while (std::getline(strStream, buffer, ',')) {
			if (kart.empty()) {
				kart = buffer;
			}
			else if (date.empty()) {
				date = buffer;
			}
			else {
				throw std::exception("");
			}
		}
		if (onlyNumeric(kart) && onlyNumeric(date)) {
			lapTimes.emplace_back(std::stoi(kart), convertToSeconds(date));
		}
		else {
			std::cout << "Not interesting line: " << oneLine;
		}
	}
	return lapTimes;
}
