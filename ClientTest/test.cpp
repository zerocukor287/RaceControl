#include "pch4clientTest.h"
#include "ClientCore.h"
#include "Race.h"

TEST(TestClient, KartsCanBeAdded) {
	ClientCore client;
	client.AddKart(1);
}

TEST(TestRace, StartTest) {
	Race race(5, {2,5,9});
	race.StartRace();
}

TEST(TestRace, WriteTest) {
	Race race(5, {2,5,9});
	race.StartRace();
	race.WriteSummaryToFile("RaceResult.csv");
}