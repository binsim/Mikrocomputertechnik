#include <Arduino.h>

#include "TFT.h"

#define Poti 34

TFT tft;

void setup()
{
    tft.TFT_Init();
}

void loop()
{
    tft.DisplayValue(analogRead(Poti));
}