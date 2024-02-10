#include "Time12H.h"

Time12H::Time12H(int hours, int minutes, int seconds)
{
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}

int Time12H::getHours()
{
    return hours_;
}

int Time12H::getMinutes()
{
    return minutes_;
}

int Time12H::getSeconds()
{
    return seconds_;
}

void Time12H::setHours(int hours)
{
    if (hours < 1 || hours > 12)
    {
        Serial.println("Invalid value for \"hours\". Allowed range: 1-12, value: " + String(hours));
        return;
    }

    hours_ = hours;
}

void Time12H::setMinutes(int minutes)
{
    if (minutes < 0 || minutes > 59)
    {
        Serial.println("Invalid value for \"minutes\". Allowed range: 0-59, value: " + String(minutes));
        return;
    }

    minutes_ = minutes;
}

void Time12H::setSeconds(int seconds)
{
    if (seconds < 0 || seconds > 59)
    {
        Serial.println("Invalid value for \"seconds\". Allowed range: 0-59, value: " + String(seconds));
        return;
    }

    seconds_ = seconds;
}
