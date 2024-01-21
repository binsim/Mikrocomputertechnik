#include <Arduino.h>

#include "TFT.h"
#include "MatrixKeypad.h"

#define Poti 34 // Poti auf den ESP32 Board
#define MAX_PIN_LENGTH 20

const uint8_t masterPin[] = {0, 9, 9, 1, 3, 6, 1, 5, 5, 1, 6};

void clearUserArray();
void matrixLoop();

int8_t userPin[MAX_PIN_LENGTH];
TFT tft; // Create an Instance of the class "TFT"
void setup()
{
	Serial.begin(9600);

	tft.TFT_Init();

	init_Keypad();

	clearUserArray();
}

void loop()
{
	tft.DisplayValue(analogRead(Poti)); // TODO: Ändern auf den gesendeten Wert
}
void matrixLoop()
{
	static Keys prevPressedKey = NONE;
	Keys pressedKey = getPressedKey();

	if (prevPressedKey == pressedKey)
		return;
	prevPressedKey = pressedKey;

	// Add delay for debouncing
	delay(20);
	// TODO: Add indicator for successfully register a new key

	int8_t iPressedKey = KeysToNumberValue(pressedKey);
	// User has entered a number
	if (iPressedKey >= 0)
	{
		Serial.println(iPressedKey);

		for (uint8_t i = 0; i < MAX_PIN_LENGTH; i++)
		{
			if (userPin[i] < 0)
			{
				userPin[i] = iPressedKey;
				return;
			}
		}

		clearUserArray();

		userPin[0] = iPressedKey;
	}

	// TODO: Add Password validation
}

void clearUserArray()
{
	for (uint8_t i = 0; i < MAX_PIN_LENGTH; i++)
	{
		userPin[i] = -1;
	}
}
