#include "pch4test.h"
#include "ServerCore.h"

#include <fstream>

class TestServerCore : public ServerCore
{
public:
	using ServerCore::ExtractInfoFromFile;
};

TEST(TestServer, ServerEvaluate) {
	ServerCore core;
	auto bestLap = core.EvaluateRaceSummary("");
	EXPECT_EQ(4, bestLap.first);
	EXPECT_EQ(54.321, bestLap.second);
}

TEST(TestServer, ReadFromFile) {
	TestServerCore core;
	std::ifstream fileStream("D:\\MYLAPS_2\\ServerTest\\TestData\\karttimes.csv", std::ifstream::in);

	auto lapTimes = core.ExtractInfoFromFile(fileStream);

	fileStream.close();
	EXPECT_EQ(25, lapTimes.size());
}
