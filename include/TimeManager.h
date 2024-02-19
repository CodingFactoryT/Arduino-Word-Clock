#include "Arduino.h"
#include "Time12H.h"
#include <WiFi.h>
#include "time.h"

#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

class TimeManager
{
public:
    TimeManager();
    Time12H formatTimeInFiveMinuteSteps(Time12H currentTime);
    void printCurrentTime();
    void printCurrentTimeFormattedInFiveMinuteSteps();
    void printCurrentTimeFormattedInFiveMinuteSteps(Time12H currentTime);
    Time12H getCurrentTime();
    void printTime(Time12H time);
    void printlnTime(Time12H time);

private:
    void configureTime();
};

#endif // TIMEMANAGER_H