// ClientCore.cpp : Defines the functions for the static library.
//

#include "pch4client.h"
#include "framework.h"

#include "ClientCore.h"

ClientCore::ClientCore() {

}

void ClientCore::AddKart(int kartNumber) {
	karts.push_back(kartNumber);
}

std::string ClientCore::RetrieveBestLap() {
	return "0:54.321";
}

std::string ClientCore::RetrieveBestKart() {
	return "Kart 2";
}
