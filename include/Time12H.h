#include "Arduino.h"

#ifndef TIME12H_H
#define TIME12H_H

class Time12H
{
public:
    Time12H(int hours, int minutes, int seconds);
    int getHours();
    int getMinutes();
    int getSeconds();
    void setHours(int hours);
    void setMinutes(int minutes);
    void setSeconds(int seconds);

private:
    int hours_;
    int minutes_;
    int seconds_;
};

#endif // TIME12H_H