// ClientCore.cpp : Defines the functions for the static library.
//

#include "pch4client.h"
#include "framework.h"

#include "ClientCore.h"
#include <format>
#include <cassert>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <comdef.h>
#ifdef max	// winsock mess it up
#undef max
#endif


ClientCore::ClientCore() {

}

void ClientCore::AddKart(int kartNumber) {
	kartNumberBuffer.insert(kartNumber);
}

void ClientCore::AddKart(std::initializer_list<int> kartNumbers) {
	for (auto kart : kartNumbers) {
		AddKart(kart);
	}
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

	race.rbegin()->SimulateRace();

	std::string fileName = std::format("Race{}.csv", race.size());
	race.rbegin()->WriteSummaryToFile(fileName);
	NotifyServer(fileName);
}

void ClientCore::NotifyServer(std::string content) {
	int wsaStatus, connectStatus;
	WSADATA WSAData;
	wsaStatus = WSAStartup(MAKEWORD(2, 0), &WSAData);
	assert(wsaStatus == NO_ERROR);

	SOCKET sock;
	SOCKADDR_IN socketIn;

	hostent* host;
	host = gethostbyname("0.0.0.0");
	assert(host != nullptr);

	socketIn.sin_addr.s_addr = *((unsigned long*)host->h_addr);	
	socketIn.sin_family = AF_INET;
	socketIn.sin_port = htons(portNumber);
	
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
	}

	connectStatus = connect(sock, (SOCKADDR*)&socketIn, sizeof(socketIn));
	if (connectStatus < 0) { 
		auto errorString = _com_error(HRESULT_FROM_WIN32(WSAGetLastError())).ErrorMessage();
		closesocket(sock);
		WSACleanup();
	}

	int iResult = send(sock, content.c_str(), content.length(), 0);
	assert(iResult != SOCKET_ERROR);

	closesocket(sock);
	WSACleanup();
}
