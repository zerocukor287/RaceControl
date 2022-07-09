#include "pch4test.h"
#include "ServerCore.h"

TEST(TestServer, ServerEvaluate) {
	ServerCore core;
	auto bestLap = core.EvaluateRaceSummary("");
	EXPECT_EQ(4, bestLap.first);
	EXPECT_EQ(54.321, bestLap.second);
}