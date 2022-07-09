#include "pch4clientTest.h"
#include "ClientCore.h"

TEST(TestClient, KartsCanBeAdded) {
	ClientCore client;
	client.AddKart(1);
}