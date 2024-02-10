#include "MessageManager.h"
#include "Display.h"

void MessageManager::displayLetter(char letter, int duration)
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
    Display::setLEDState(alphabet[abcArrayIndex], Display::DISPLAY_COLOR);
    FastLED.show();

    delay(duration);

    Display::setLEDState(alphabet[abcArrayIndex], Display::OFF);
    FastLED.show();
}

void MessageManager::displayMessage(String message, int delayBetweenCharacters, int delayBetweenWords)
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

void MessageManager::displayQuestionMark(int duration)
{
    for (uint16_t i = 0; i < (sizeof(questionMark) / sizeof(questionMark[0])); i++)
    {
        Display::setLEDState(questionMark[i], Display::DISPLAY_COLOR);
    }

    FastLED.show();
    delay(duration);

    for (uint16_t i = 0; i < (sizeof(questionMark) / sizeof(questionMark[0])); i++)
    {
        Display::setLEDState(questionMark[i], Display::OFF);
    }

    FastLED.show();
}