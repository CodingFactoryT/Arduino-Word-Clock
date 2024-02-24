#include "TimeManager.h"
#include "Display.h"

Time12H TimeManager::getCurrentTime()
{
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        delay(100);
    }

    int hours = timeinfo.tm_hour;
    int minutes = timeinfo.tm_min;
    int seconds = timeinfo.tm_sec;

    if (hours >= 13)
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

    int wifiAnimationStatus = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        Display::clear();

        switch (wifiAnimationStatus)
        {
        case 0:
            Display::activateLEDs(WLAN_ANIMATION_PART1, 1);
            break;
        case 1:
            Display::activateLEDs(WLAN_ANIMATION_PART2, 6);
            break;
        case 2:
            Display::activateLEDs(WLAN_ANIMATION_PART3, 17);
            break;
        }

        FastLED.show();

        wifiAnimationStatus = (wifiAnimationStatus + 1) % 3;
        Serial.print(".");
        delay(500);
    }

    Serial.println(" CONNECTED");
    Display::clear();
    Serial.print("Configuring Time ");
    struct tm timeinfo;

    Display::activateLEDs(TIME_CONFIG, 22);
    FastLED.show();
    do
    {
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        Serial.print(".");
        delay(100);
    } while (!getLocalTime(&timeinfo));

    Serial.println("Time configuration completed");
    Display::clear();
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