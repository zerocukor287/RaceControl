#include "pch4test.h"
#include "ServerCore.h"

#include <fstream>

class TestServerCore : public ServerCore
{
public:
	using ServerCore::ExtractInfoFromFile;
	using ServerCore::GetBestLap;
};

TEST(TestServer, ServerEvaluateNull) {
	ServerCore core;
	auto bestLap = core.EvaluateRaceSummary("");
	EXPECT_EQ(0, bestLap.first);
	EXPECT_NEAR(std::numeric_limits<double>::max(), bestLap.second, 0.0001);
}

TEST(TestServer, ServerEvaluate) {
	ServerCore core;
	auto bestLap = core.EvaluateRaceSummary("D:\\MYLAPS_2\\ServerTest\\TestData\\karttimes.csv");
	EXPECT_EQ(5, bestLap.first);
	EXPECT_NEAR(56, bestLap.second, 0.0001);
}

TEST(TestServer, ReadFromFile) {
	TestServerCore core;
	std::ifstream fileStream("D:\\MYLAPS_2\\ServerTest\\TestData\\karttimes.csv", std::ifstream::in);

	auto lapTimes = core.ExtractInfoFromFile(fileStream);

	fileStream.close();
	EXPECT_EQ(25, lapTimes.size());
}

TEST(TestServer, GetBestLap) {
	TestServerCore core;
	std::vector<trackTimeByKart> times{{0,0.0}, {0,0.0}};
	auto bestLap = core.GetBestLap(times);
	EXPECT_EQ(times[0].first, bestLap.first);
	EXPECT_NEAR(0.0, bestLap.second, 0.0001);
}

TEST(TestServer, GetBestLapOf3) {
	TestServerCore core;
	std::vector<trackTimeByKart> times{{0,0.0},
									   {0,1.3},		//lap: 1.3
									   {0,2.59},	//lap: 1.29
									   {0,3.9}};	//lap: 1.31
	auto bestLap = core.GetBestLap(times);
	EXPECT_EQ(times[0].first, bestLap.first);
	EXPECT_NEAR(1.29, bestLap.second, 0.0001);
}
