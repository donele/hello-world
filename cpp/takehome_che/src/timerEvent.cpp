
#include "xtime.h"
#include <thread>
#include <iostream>
#include <sstream>

using namespace std;

string formatTimeDifference(TPOINT t1, TPOINT t2)
{
	auto tdiff = t1 - t2;
	auto diffSec = std::chrono::duration_cast<std::chrono::seconds>(tdiff).count();
	auto days = diffSec / 86400;
	auto hours = (diffSec - days * 86400) / 3600;
	auto minutes = (diffSec - days * 86400 - hours * 3600) / 60;
	auto seconds = diffSec % 60;
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(tdiff).count() % 1000000;
	stringstream ss;
	ss << days << "days " << hours << "hours " << minutes << "minutes " << seconds << "seconds "
		<< microseconds << "us";
	return ss.str();
}

bool printNow(void *)
{
	static auto tp = str2tp("20230101 12:35:42.12345678");
	auto curTime = currentTime();
	cout << "now: " << tp2str(curTime) << " ,diff: " << formatTimeDifference(curTime, tp) << endl;
	return true;
}

void bkgTask(int n)
{
	auto stime = currentTime();
	auto interval = std::chrono::microseconds(1000000);
	auto etime = stime + interval * n;
	Timer timer(stime, etime, interval, printNow, nullptr);

	auto scheduler = Scheduler::instance();
	scheduler->addTimer(timer);

	while(true)
	{
		if (currentTime() >= scheduler->getNextTime())
			scheduler->run();

		auto curTime = currentTime();
		auto ntime = scheduler->getNextTime();
		if (ntime == chrono::system_clock::time_point::max())
			break;

		std::this_thread::sleep_for(ntime - curTime);
	}
}

int main()
{
	int nprint = 10; // number of prints
	std::thread my_thread(bkgTask, nprint);
	my_thread.join();
}