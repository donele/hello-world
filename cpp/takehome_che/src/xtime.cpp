

#include "xtime.h"
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;


// string to time point
TPOINT
str2tp(const string& tstr, 
       const string& format)
{
  tm t;
  istringstream iss(tstr);
  iss >> get_time(&t, format.c_str());
  if (iss.fail()) {
    cerr << "Failed to parse time string: " << tstr
	      << " with format " << format << endl; 
    return TPOINT();
  }

  auto tp = chrono::system_clock::from_time_t(mktime(&t));
  
  // find the microseconds
  auto pos = tstr.rfind(".");
  if (pos != string::npos) {
    auto usStr = tstr.substr(pos + 1, 6);
    try {
      auto usInt = stoi(usStr);
      tp += std::chrono::microseconds(usInt);
    } catch(...) {}
  }

  return tp;
}

//time point to string

string tp2str(const TPOINT& tp,
              const string& format)
{
  time_t t = chrono::system_clock::to_time_t(tp);
  stringstream ss1;
  ss1 << put_time(localtime(&t), format.c_str());
  if (ss1.fail()) {
    cerr << "Failed to format time string: " << endl;
    return "";
  }

  // append microseconds
  auto us = chrono::duration_cast< 
  std::chrono::microseconds >(tp.time_since_epoch() ).count() % 1000000 ;

  stringstream ss2;
  ss2 << std::setw(6) << std::setfill('0') << us;

  return ss1.str() + "." + ss2.str();
}

TPOINT currentTime()
{
  return std::chrono::system_clock::now();
}

Scheduler* Scheduler::instance()
{
    static Scheduler scheduler;
    return &scheduler;
}

void Scheduler::run()
{
    while (!timers_.empty())
    {
        auto curTime = currentTime();
        if (timers_.begin()->nextRunTime > curTime)
            break;

        auto timer = *(timers_.begin());
        timers_.erase(timers_.begin());
        auto success = timer.process();

        if (success)
            addTimer(timer);
    }
}

void Scheduler::addTimer(Timer timer)
{
  auto curTime = currentTime();
  while ((timer.nextRunTime < curTime) && (timer.nextRunTime <= timer.endTime))
      timer.nextRunTime += timer.interval;

  if (timer.nextRunTime > timer.endTime)
      return;

  timers_.insert(timer);
}

TPOINT Scheduler::getNextTime()
{
    if (timers_.empty())
        return chrono::system_clock::time_point::max();

    return timers_.begin()->nextRunTime;
}
