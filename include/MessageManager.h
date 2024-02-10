#include "Arduino.h"
#include "FastLED.h"

#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

const int questionMark[] = {26, 27, 37, 50, 60, 82};
const String availableCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXZ";
const int alphabet[] = {40, 47, 39, 67, 63, 73, 42, 38, 27, 34, 2, 46, 33, 61, 36, 54, 48, 23, 60, 5, 82, 80, 50, 98, -1, 49};

class MessageManager
{
public:
    void displayLetter(char letter, int duration);
    void displayMessage(String message, int delayBetweenCharacters, int delayBetweenWords);
    void displayQuestionMark(int duration);
};

#endif // MESSAGEMANAGER_H