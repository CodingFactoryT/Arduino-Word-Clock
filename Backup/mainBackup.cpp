/* #include <Arduino.h>
#include "FastLED.h"
#include "Time12H.h"

const int Es[] = {0, 1};
const int Ist[] = {3, 4, 5};
const int Fuenf_BEFORE[] = {7, 8, 9, 10};
const int Zehn_BEFORE[] = {18, 19, 20, 21};
const int Zwanzig_BEFORE[] = {11, 12, 13, 14, 15, 16, 17};
const int Dreiviertel_BEFORE[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
const int Viertel_BEFORE[] = {26, 27, 28, 29, 30, 31, 32};
const int Nach[] = {38, 39, 40, 41};
const int Vor[] = {35, 36, 37};
const int Halb[] = {44, 45, 46, 47};
const int Zwoelf[] = {49, 50, 51, 52, 53, 54};
const int Zwei[] = {62, 63, 64, 65};
const int Eins[] = {60, 61, 62, 63};
const int Sieben[] = {55, 56, 57, 58, 59, 60};
const int Drei[] = {67, 68, 69, 70};
const int Fuenf[] = {73, 74, 75, 76};
const int Elf[] = {85, 86, 87};
const int Neun[] = {81, 82, 83, 84};
const int Vier[] = {77, 78, 79, 80};
const int Acht[] = {89, 90, 91, 92};
const int Zehn[] = {93, 94, 95, 96};
const int Sechs[] = {104, 105, 106, 107, 108};
const int Uhr[] = {100, 101, 102};

const int questionMark[] = {26, 27, 37, 50, 60, 82};
const String availableCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXZ";
const int abc[] = {40, 47, 39, 67, 63, 73, 42, 38, 27, 34, 2, 46, 33, 61, 36, 54, 48, 23, 60, 5, 82, 80, 50, 98, -1, 49};

#define LED_STRIP_LENGTH 110
#define DATA_PIN 5

CRGB ledStrip[LED_STRIP_LENGTH];
const CRGB DEFAULT_COLOR = CRGB::White;
const CRGB OFF = CRGB::Black;
const int BRIGHTNESS = 255;

void displayQuestionMark(int duration)
{
  for (uint16_t i = 0; i < (sizeof(questionMark) / sizeof(questionMark[0])); i++)
  {
    ledStrip[questionMark[i]] = DEFAULT_COLOR;
  }

  FastLED.show();
  delay(duration);

  for (uint16_t i = 0; i < (sizeof(questionMark) / sizeof(questionMark[0])); i++)
  {
    ledStrip[questionMark[i]] = CRGB::Black;
  }

  FastLED.show();
}

void displayLetter(char letter, int duration)
{
  if (letter > 'Z')
  {
    letter -= 'a' - 'A'; // convert to upper case
  }

  if (availableCharacters.indexOf(letter) == -1)
  {
    Serial.println("The message contains an \"" + String(letter) + "\" which is not available in the word clock. A \"?\" is displayed instead");
    displayQuestionMark(duration);
    return;
  }

  int abcArrayIndex = letter - 'A';
  ledStrip[abc[abcArrayIndex]] = DEFAULT_COLOR;
  FastLED.show();

  delay(duration);

  ledStrip[abc[abcArrayIndex]] = OFF;
  FastLED.show();
}

void displayMessage(String message, int delayBetweenCharacters, int delayBetweenWords)
{
  message.toUpperCase();

  for (uint16_t i = 0; i < message.length(); i++)
  {
    if (message.charAt(i) == ' ')
    {
      delay(delayBetweenWords);
      continue;
    }

    displayLetter(message.charAt(i), delayBetweenCharacters);
  }
}

void turnOnMultipleLEDs(const int *ledIndecesToActivate, int arraySize)
{
  for (int i = 0; i < arraySize; i++)
  {
    ledStrip[ledIndecesToActivate[i]] = DEFAULT_COLOR;
  }
}

void turnOffAllLEDs()
{
  for (int i = 0; i < LED_STRIP_LENGTH; i++)
  {
    ledStrip[i] = CRGB::Black;
  }

  FastLED.show();
}

Time12H getCurrentTimeFormattedInFiveMinuteSteps()
{
  return Time12H(0, 0, 0);
}

void displayTime()
{
  turnOffAllLEDs();
  turnOnMultipleLEDs(Es, 2);
  turnOnMultipleLEDs(Ist, 3);

  switch (getCurrentTimeFormattedInFiveMinuteSteps().getHours())
  {
  case 1:
    turnOnMultipleLEDs(Eins, 4);
    break;
  case 2:
    turnOnMultipleLEDs(Zwei, 4);
    break;
  case 3:
    turnOnMultipleLEDs(Drei, 4);
    break;
  case 4:
    turnOnMultipleLEDs(Vier, 4);
    break;
  case 5:
    turnOnMultipleLEDs(Fuenf, 4);
    break;
  case 6:
    turnOnMultipleLEDs(Sechs, 5);
    break;
  case 7:
    turnOnMultipleLEDs(Sieben, 6);
    break;
  case 8:
    turnOnMultipleLEDs(Acht, 4);
    break;
  case 9:
    turnOnMultipleLEDs(Neun, 4);
    break;
  case 10:
    turnOnMultipleLEDs(Zehn, 4);
    break;
  case 11:
    turnOnMultipleLEDs(Elf, 3);
    break;
  case 12:
    turnOnMultipleLEDs(Zwoelf, 5);
    break;
  default:
    Serial.println("ERROR: hours_formatted has an unallowed value");
    break;
  }

  switch (getCurrentTimeFormattedInFiveMinuteSteps().getMinutes())
  {
  case 0:
    turnOnMultipleLEDs(Uhr, 3);
    break;
  case 5:
    turnOnMultipleLEDs(Fuenf_BEFORE, 4);
    turnOnMultipleLEDs(Nach, 4);
    break;
  case 10:
    turnOnMultipleLEDs(Zehn_BEFORE, 4);
    turnOnMultipleLEDs(Nach, 4);
    break;
  case 15:
    turnOnMultipleLEDs(Viertel_BEFORE, 7);
    turnOnMultipleLEDs(Nach, 4);
    break;
  case 20:
    turnOnMultipleLEDs(Zwanzig_BEFORE, 7);
    turnOnMultipleLEDs(Nach, 4);
    break;
  case 25:
    turnOnMultipleLEDs(Fuenf_BEFORE, 4);
    turnOnMultipleLEDs(Vor, 3);
    turnOnMultipleLEDs(Halb, 4);
    break;
  case 30:
    turnOnMultipleLEDs(Halb, 4);
    break;
  case 35:
    turnOnMultipleLEDs(Fuenf_BEFORE, 5);
    turnOnMultipleLEDs(Nach, 4);
    turnOnMultipleLEDs(Halb, 4);
    break;
  case 40:
    turnOnMultipleLEDs(Zwanzig_BEFORE, 7);
    turnOnMultipleLEDs(Vor, 3);
    break;
  case 45:
    turnOnMultipleLEDs(Viertel_BEFORE, 7);
    turnOnMultipleLEDs(Vor, 3);
    break;
  case 50:
    turnOnMultipleLEDs(Zehn_BEFORE, 4);
    turnOnMultipleLEDs(Vor, 3);
    break;
  case 55:
    turnOnMultipleLEDs(Fuenf_BEFORE, 4);
    turnOnMultipleLEDs(Vor, 3);
    break;
  default:
    Serial.println("ERROR: minutes_formatted has an unallowed value");
    break;
  }

  FastLED.show();
}

void configureTime()
{
}

Time12H getCurrentTime()
{
  return Time12H(0, 0, 0);
}

int *formatTime(int hours, int minutes, int seconds)
{
  return nullptr;
}

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(ledStrip, LED_STRIP_LENGTH); // GRB ordering is typical
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  displayMessage("Hallo das hat funktioniert Was ist das y Fragezeichen", 500, 1000);

  /* displayTime();
  delay(1000); */
}
* /