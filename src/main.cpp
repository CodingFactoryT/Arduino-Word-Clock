#include <Arduino.h>
#include "Display.h"
Display *display = nullptr;

int testHours = 11;
int testMinutes = 40;
int testSeconds = 0;

void testDisplayTime()
{
  testSeconds++;
  if (testSeconds >= 60)
  {
    testSeconds = 0;
    testMinutes++;
    if (testMinutes >= 60)
    {
      testMinutes = 0;
      testHours++;
      if (testHours >= 13)
      {
        testHours = 1;
      }
    }
  }

  Time12H currentTime = Time12H(testHours, testMinutes, testSeconds);
  display->displayTime(currentTime);
  delay(8);
}

void setup()
{
  Serial.begin(9600);
  display = new Display();
  Serial.println("Setup complete");
}

void loop()
{
  Time12H currentTime = display->timeManager.getCurrentTime();
  display->displayTime(currentTime);
  delay(1000);
  // testDisplayTime();
}