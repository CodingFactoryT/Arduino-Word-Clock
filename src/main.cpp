#include <Arduino.h>
#include "Display.h"
Display *display = nullptr;

void setup()
{
  Serial.begin(9600);
  display = new Display();
  Serial.println("Setup complete");
}

void loop()
{
  display->displayTime();
  delay(25000);
}