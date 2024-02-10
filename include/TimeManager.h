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
    Time12H getCurrentTimeFormattedInFiveMinuteSteps();
    void printCurrentTime();
    void printCurrentTimeFormattedInFiveMinuteSteps();

private:
    Time12H getCurrentTime();
    void configureTime();
};

#endif // TIMEMANAGER_H