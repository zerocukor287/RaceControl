// ServerCore.cpp : Defines the functions for the static library.
//

#include "pch4serverCore.h"

#include "ServerCore.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>

#include <WinSock2.h>
#ifdef max	// winsock mess it up
#undef max
#endif

ServerCore::ServerCore() {

}

void ServerCore::Listen() {
	int wsaStatus;
	WSADATA WSAData;
	wsaStatus = WSAStartup(MAKEWORD(2, 0), &WSAData);
	if (wsaStatus != NO_ERROR) {
		std::cout << "WSA Startup failed with error : " << wsaStatus;
	}

	SOCKET sock;
	SOCKADDR_IN socketIn;

	socketIn.sin_addr.s_addr = htonl(INADDR_ANY);
	socketIn.sin_family = AF_INET;	// local networks
	socketIn.sin_port = htons(portNumber);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cout << "Invalid socket " << WSAGetLastError();
		WSACleanup();
		return;
	}

	auto bindReturn = bind(sock, (SOCKADDR*)&socketIn, sizeof(socketIn));
	if (bindReturn > 0) {
		std::cout << "Cannot bind port " << WSAGetLastError();
		WSACleanup();
		return;
	}

	char buffer[255];

	listen(sock, 1);
	while (true) {

		int sizeof_sin = sizeof(socketIn);
		sock = accept(sock, (SOCKADDR*)&socketIn, &sizeof_sin);
		if (sock != INVALID_SOCKET) {
			recv(sock, buffer, sizeof(buffer), 0);
			closesocket(sock);
			auto summary = EvaluateRaceSummary(buffer);
		}
		else {
		}
	}

	WSACleanup();
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
	trackTimeByKart bestLap {0, std::numeric_limits<double>::max()};
	try {
		std::ifstream fileStream(filePath, std::ifstream::in);
		auto lapTimes = ExtractInfoFromFile(fileStream);
		fileStream.close();

		bestLap = GetBestLap(lapTimes);
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	return bestLap;
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
			std::cout << "Not interesting line: " << oneLine << "\n";
		}
	}
	return lapTimes;
}

trackTimeByKart ServerCore::GetBestLap(const std::vector<trackTimeByKart>& laps) {
	std::map<int, double> bestLapByKarts;
	std::map<int, double> previousLapByKarts;

	for (const auto& lap : laps) {
		if (previousLapByKarts.find(lap.first) != previousLapByKarts.end()) {
			// kart already finished one lap
			double lapTime = lap.second - previousLapByKarts.at(lap.first);
			if (bestLapByKarts.find(lap.first) == bestLapByKarts.end()) {
				// no best lap yet
				bestLapByKarts.insert({lap.first, lapTime});
			} else if (lapTime < bestLapByKarts.at(lap.first)) {
				// better than before
				bestLapByKarts[lap.first] = lapTime;
			}
			// setting prevoius lap to current
			previousLapByKarts[lap.first] = lap.second;
		}
		else {
			previousLapByKarts.insert(lap);
		}
	}

	trackTimeByKart bestLap {0, std::numeric_limits<double>::max()};
	for (const auto& kartLap : bestLapByKarts) {
		if (bestLap.second > kartLap.second) {
			bestLap = kartLap;
		}
	}
	return bestLap;
}
