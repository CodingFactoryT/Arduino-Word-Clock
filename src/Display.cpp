#include "Display.h"

CRGB Display::OFF = CRGB::Black;
CRGB Display::DISPLAY_COLOR = CRGB::White;
CRGB Display::ledStrip[LED_AMOUNT];

Display::Display()
{
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(ledStrip, LED_AMOUNT); // GRB ordering is typical
    setBrightness(BRIGHTNESS);
}

void Display::setBrightness(int brightness)
{
    FastLED.setBrightness(brightness);
}

void Display::clear()
{
    for (int i = 0; i < LED_AMOUNT; i++)
    {
        setLEDState(i, OFF);
    }

    FastLED.show();
}

void Display::displayTime()
{
    clear();
    activateLEDs(Es, 2);
    activateLEDs(Ist, 3);

    Time12H currentTimeFormatted = timeManager.getCurrentTimeFormattedInFiveMinuteSteps();
    if (currentTimeFormatted.getMinutes() >= 25) // after 25 minutes, the "Nach" changes to "Vor". Thus, the hour must be incremented by 1
    {
        currentTimeFormatted.setHours(currentTimeFormatted.getHours() + 1);
    }
    switch (currentTimeFormatted.getHours())
    {
    case 1:
        activateLEDs(Eins, 4);
        break;
    case 2:
        activateLEDs(Zwei, 4);
        break;
    case 3:
        activateLEDs(Drei, 4);
        break;
    case 4:
        activateLEDs(Vier, 4);
        break;
    case 5:
        activateLEDs(Fuenf, 4);
        break;
    case 6:
        activateLEDs(Sechs, 5);
        break;
    case 7:
        activateLEDs(Sieben, 6);
        break;
    case 8:
        activateLEDs(Acht, 4);
        break;
    case 9:
        activateLEDs(Neun, 4);
        break;
    case 10:
        activateLEDs(Zehn, 4);
        break;
    case 11:
        activateLEDs(Elf, 3);
        break;
    case 12:
        activateLEDs(Zwoelf, 5);
        break;
    default:
        Serial.println("ERROR: hours_formatted has an unallowed value");
        break;
    }

    switch (currentTimeFormatted.getMinutes())
    {
    case 0:
        activateLEDs(Uhr, 3);
        break;
    case 5:
        activateLEDs(Fuenf_BEFORE, 4);
        activateLEDs(Nach, 4);
        break;
    case 10:
        activateLEDs(Zehn_BEFORE, 4);
        activateLEDs(Nach, 4);
        break;
    case 15:
        activateLEDs(Viertel_BEFORE, 7);
        activateLEDs(Nach, 4);
        break;
    case 20:
        activateLEDs(Zwanzig_BEFORE, 7);
        activateLEDs(Nach, 4);
        break;
    case 25:
        activateLEDs(Fuenf_BEFORE, 4);
        activateLEDs(Vor, 3);
        activateLEDs(Halb, 4);
        break;
    case 30:
        activateLEDs(Halb, 4);
        break;
    case 35:
        activateLEDs(Fuenf_BEFORE, 5);
        activateLEDs(Nach, 4);
        activateLEDs(Halb, 4);
        break;
    case 40:
        activateLEDs(Zwanzig_BEFORE, 7);
        activateLEDs(Vor, 3);
        break;
    case 45:
        activateLEDs(Viertel_BEFORE, 7);
        activateLEDs(Vor, 3);
        break;
    case 50:
        activateLEDs(Zehn_BEFORE, 4);
        activateLEDs(Vor, 3);
        break;
    case 55:
        activateLEDs(Fuenf_BEFORE, 4);
        activateLEDs(Vor, 3);
        break;
    default:
        Serial.println("ERROR: minutes_formatted has an unallowed value");
        break;
    }

    FastLED.show();
}

void Display::activateLEDs(const int *ledIndecesToActivate, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        setLEDState(ledIndecesToActivate[i], DISPLAY_COLOR);
    }
}

void Display::setLEDState(int index, CRGB color)
{
    ledStrip[index] = color;
}