#include "TimeManager.h"

TimeManager::TimeManager()
{
    configureTime();
}

Time12H TimeManager::getCurrentTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        Time12H failedTime = Time12H(-1, -1, -1);
        return failedTime;
    }

    int hours = timeinfo.tm_hour;
    int minutes = timeinfo.tm_min;
    int seconds = timeinfo.tm_sec;

    if (hours > 12)
    {
        hours -= 12;
    }

    Time12H currentTime = Time12H(hours, minutes, seconds);
    return currentTime;
}

Time12H TimeManager::formatTimeInFiveMinuteSteps(Time12H currentTime)
{
    /* printTime(currentTime);
    Serial.print(" -> "); */
    int remainder_int = currentTime.getMinutes() % 5;
    float remainder_float = remainder_int;

    if (remainder_int == 2 && currentTime.getSeconds() >= 30)
    {
        remainder_float += 0.5f;
    }

    int formattedHours = currentTime.getHours();
    int formattedMinutes = currentTime.getMinutes();

    if (remainder_float >= 2.5f)
    {
        formattedMinutes += 5 - remainder_int;
        formattedMinutes %= 60;
    }
    else
    {
        formattedMinutes -= remainder_int;
    }

    if (formattedMinutes == 0 && currentTime.getMinutes() >= 55)
    {
        formattedHours++;
        if (formattedHours >= 13)
        {
            formattedHours = 1;
        }
    }

    Time12H formattedTime = Time12H(formattedHours, formattedMinutes, 0);
    /* printlnTime(formattedTime); */
    return formattedTime;
}

#include "WIFICredetentials.h" //a file that contains two const char pointers, "ssid" and "password"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void TimeManager::configureTime()
{
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" CONNECTED");
    Serial.print("Configuring Time ");
    struct tm timeinfo;
    do
    {
        Serial.print(".");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        delay(100);
    } while (!getLocalTime(&timeinfo));

    Serial.println("Time configuration completed");

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}

void TimeManager::printCurrentTime()
{
    Time12H currentTime = getCurrentTime();
    Serial.println(String(currentTime.getHours()) + ":" + String(currentTime.getMinutes()) + ":" + String(currentTime.getSeconds()));
}

void TimeManager::printCurrentTimeFormattedInFiveMinuteSteps(Time12H currentTime)
{
    Time12H currentFormattedTime = formatTimeInFiveMinuteSteps(currentTime);
    printlnTime(currentFormattedTime);
}

void TimeManager::printCurrentTimeFormattedInFiveMinuteSteps()
{
    Time12H currentTime = getCurrentTime();
    printCurrentTimeFormattedInFiveMinuteSteps(currentTime);
}

void TimeManager::printTime(Time12H time)
{
    Serial.print(String(time.getHours()) + ":" + String(time.getMinutes()) + ":" + String(time.getSeconds()));
}

void TimeManager::printlnTime(Time12H time)
{
    printTime(time);
    Serial.println();
}