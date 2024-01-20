#include <Arduino.h>

#include "TFT.h"

#define Poti 34 // Poti auf den ESP32 Board

TFT tft; // Create an Instance of the class "TFT"

void setup()
{
    tft.TFT_Init();
}

void loop()
{
    tft.DisplayValue(analogRead(Poti)); // TODO: Ändern auf den gesendeten Wert
}