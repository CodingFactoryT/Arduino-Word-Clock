#include "FastLED.h"
#include "MessageManager.h"
#include "TimeManager.h"

#ifndef DISPLAY_H
#define DISPLAY_H

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

#define LED_AMOUNT 110
#define DATA_PIN 5
#define BRIGHTNESS 255

class Display
{
public:
    Display();
    MessageManager messageManager;
    TimeManager timeManager;
    void setBrightness(int brightness);
    void clear();
    void displayTime();
    void activateLEDs(const int *ledIndecesToActivate, int arraySize);
    static void setLEDState(int index, CRGB color);
    static CRGB OFF;
    static CRGB DISPLAY_COLOR;

private:
    static CRGB ledStrip[LED_AMOUNT];
};

#endif; // DISPLAY_H