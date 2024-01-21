#include <Arduino.h>

#include "TFT.h"
#include "MatrixKeypad.h"

#define Poti 34 // Poti auf den ESP32 Board
#define MAX_PIN_LENGTH 18
#define DEBOUNCE_DELAY 50

const String masterPin = "09913615516";
String userPin = "1234";

void matrixLoop();

TFT tft; // Create an Instance of the class "TFT"
void setup()
{
    Serial.begin(9600);

    tft.TFT_Init();

    init_Keypad();
}

void loop()
{
    tft.DisplayValue(analogRead(Poti)); // TODO: Ändern auf den gesendeten Wert

    matrixLoop();
}
void matrixLoop()
{
    static String inputPin = "";
    static char prevPressedKey = 0;
    static unsigned long lastDebounceTime = 0;
    char pressedKey = getPressedKey();

    if (prevPressedKey == pressedKey)
        return;
    prevPressedKey = pressedKey;

    if ((millis() - lastDebounceTime) <= DEBOUNCE_DELAY)
        return;
    lastDebounceTime = millis();

    // Not a valid key for pin
    if (pressedKey == 0)
        return;

    // TODO: Add indicator for successfully register a new key

    if (pressedKey == '*')
    {
        // Reset pin
        inputPin = "";
        tft.updatePin(inputPin);

        return;
    }
    else if (pressedKey == '#')
    {
        if (inputPin == masterPin || inputPin == userPin)
        {
            // TODO: Open Relay
            Serial.println("Open Relay");
        }
        else if (inputPin == "")
        {
            // TODO: Close Relay
            Serial.println("Close Relay");
        }

        // Reset pin
        inputPin = "";
        tft.updatePin(inputPin);

        return;
    }
    if (inputPin.length() >= MAX_PIN_LENGTH) // Max Pin Length reached
        return;
    inputPin += pressedKey;
    Serial.println(inputPin);
    tft.updatePin(inputPin);
}
