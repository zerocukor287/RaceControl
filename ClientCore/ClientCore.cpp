// ClientCore.cpp : Defines the functions for the static library.
//

#include "pch4client.h"
#include "framework.h"

#include "ClientCore.h"

ClientCore::ClientCore() {

}

void ClientCore::AddKart(int kartNumber) {
	kartNumberBuffer.insert(kartNumber);
}

std::string ClientCore::RetrieveBestLap() {
	return "0:54.321";
}

std::string ClientCore::RetrieveBestKart() {
	return "Kart 2";
}

void ClientCore::StartNewRace() {
	race.emplace_back(Race(lapNumber, kartNumberBuffer));

	lapNumber = 0;
	kartNumberBuffer.clear();
}
