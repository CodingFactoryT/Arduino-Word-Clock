// TODO implement brightness sensor for adjusting the brightness of the display (light=high brightness, dark = low brightness)
// TODO implement time zones where the clock should stay off
#include <Arduino.h>
#include "Display.h"

#define PIR 26 // motion sensor pin

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
  pinMode(PIR, INPUT);

  display = new Display();
  display->timeManager.configureTime();

  Serial.println("Setup complete");
}

bool isDisplayOn = false;
void loop()
{
  if (digitalRead(PIR))
  {
    if (!isDisplayOn)
    {
      display->setShouldUpdate(true);
    }

    Time12H currentTime = display->timeManager.getCurrentTime();
    display->displayTime(currentTime);
    isDisplayOn = true;
  }
  else if (isDisplayOn)
  {
    display->clear();
    isDisplayOn = false;
  }

  delay(250);

  // testDisplayTime();
}