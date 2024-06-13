
#pragma once

#include <chrono>
#include <string>
#include <functional>
#include <set>

using TPOINT=std::chrono::time_point<std::chrono::system_clock>;
using Callback=std::function<bool (void* )>;

TPOINT
str2tp(const std::string& tstr, 
       const std::string& format= "%Y%m%d %H:%M:%S");

std::string tp2str(const TPOINT& tp,
	      const std::string& format= "%Y%m%d %H:%M:%S");


TPOINT currentTime();

struct Timer {

    TPOINT nextRunTime;
    TPOINT endTime;
    std::chrono::microseconds interval;  //repeat time interval
    Callback callback;
    void* userParam = nullptr;

    bool process() const {
        return callback(userParam);
    }

    Timer(TPOINT stime, TPOINT etime, std::chrono::microseconds intvl, Callback cb, void * up) :
            nextRunTime(stime), endTime(etime), interval(intvl), 
 			callback(cb), userParam(up)
    {}

};

struct TimerCMP {
    bool operator() (Timer t1, Timer t2) const {
        return t1.nextRunTime < t2.nextRunTime;
    }
};

class Scheduler
{
public:

    static Scheduler* instance();

    void run();
    void addTimer(Timer timer);
    TPOINT getNextTime();

protected:
    Scheduler() = default;

    std::set<Timer, TimerCMP> timers_;
};
