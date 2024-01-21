#include <Arduino.h>

#include "TFT.h"
#include "MatrixKeypad.h"

#define Poti 34 // Poti auf den ESP32 Board
#define MAX_PIN_LENGTH 20

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
}
void matrixLoop()
{
    static String inputPin = "";
    static char prevPressedKey = 0;
    char pressedKey = getPressedKey();

    if (prevPressedKey == pressedKey)
        return;
    prevPressedKey = pressedKey;

    // Not a valid key for pin
    if (pressedKey == 0)
        return;

    // Add delay for debouncing
    delay(20);

    // TODO: Add indicator for successfully register a new key

    if (pressedKey == '*')
    {
        // Reset pin
        inputPin = "";

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

        return;
    }

    inputPin += pressedKey;
    Serial.println(inputPin);
}
