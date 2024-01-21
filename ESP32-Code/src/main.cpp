#include <Arduino.h>

#include "FlashUtil.h"
#include "TFT.h"
#include "MatrixKeypad.h"
#include "Communication.h"

#define LED_GREEN 2
#define MAX_PIN_LENGTH 18
#define DEBOUNCE_DELAY 50

const String masterPin = "09913615516";

// Region FunctionDeclaration
void sendRelayOpen(bool open);
void matrixLoop();
// EndRegion FunctionDeclaration

TFT tft; // Create an Instance of the class "TFT"
FlashUtil flashUtil;
void setup()
{
    Serial.begin(9600);

    pinMode(LED_GREEN, OUTPUT);

    // Show if esp now is successfully initialized with green led
    digitalWrite(LED_GREEN, initCommunication() == ESP_OK ? HIGH : LOW);

    // Initialize TFT Display
    tft.TFT_Init();

    init_Keypad();
}

void loop()
{
    matrixLoop();
}

void matrixLoop()
{
    static String inputPin = "";
    static char prevPressedKey = 0;
    static unsigned long lastDebounceTime = 0;
    static bool inChangePin = false;
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
        if (!inChangePin)
        {
            if (inputPin == masterPin || inputPin == flashUtil.getPin())
            {
                Serial.println("Open Relay");
                sendRelayOpen(true);
            }
            else if (inputPin == "")
            {
                Serial.println("Close Relay");
                sendRelayOpen(false);
            }
        }
        else
        {
            static String checkChangePin = "";

            if (checkChangePin != "")
            {
                if (checkChangePin == inputPin)
                {
                    flashUtil.setPin(inputPin); // save user pin to flash
                }
                else
                {
                    // Pin are not the same

                    // TODO: show user
                }
                checkChangePin = "";

                // Exit pin change state
                inChangePin = false;
            }
            else
            {
                checkChangePin = inputPin;
            }
        }

        // Reset pin
        inputPin = "";
        tft.updatePin(inputPin);

        return;
    }
    else if (pressedKey == 'A' || pressedKey == 'B' || pressedKey == 'C' || pressedKey == 'D')
    {
        if (pressedKey == 'B')
        {
            inChangePin = true;
        }

        return;
    }

    if (inputPin.length() >= MAX_PIN_LENGTH) // Max Pin Length reached
        return;

    inputPin += pressedKey;
    Serial.println(inputPin);
    tft.updatePin(inputPin);
}

void onEspNowCallback(const uint8_t *macAddr, const uint8_t *incomingData, int len)
{
    // Allow for only 2 byte length data, to not throw any errors
    if (len == 2)
    {
        // Convert data for displaying
        uint16_t data = (incomingData[0] << 8) + incomingData[1];
        // Serial.println(data, HEX);

        // set display value to received poti value
        tft.DisplayValue(data);
    }
}

void sendRelayOpen(bool open)
{
    // Convert data to be able to be sent
    const uint8_t data = (uint8_t)open;

    // Send data
    esp_now_send(receiverAddress, &data, 1);
}