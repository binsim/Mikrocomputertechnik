#include <Arduino.h>

#include "TFT.h"
#include "MatrixKeypad.h"

#define Poti 34 // Poti auf den ESP32 Board

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

	getPressedKey();
}