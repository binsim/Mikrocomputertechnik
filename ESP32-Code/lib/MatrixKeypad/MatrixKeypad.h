#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#include <Arduino.h>
#include <Wire.h>

#define PCF8574_ADDRESS 0x20

void init_Keypad();
char getPressedKey();

#endif // MATRIX_KEYPAD_H