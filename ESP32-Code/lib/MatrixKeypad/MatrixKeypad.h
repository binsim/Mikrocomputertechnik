#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#include <Arduino.h>
#include <Wire.h>

enum Keys
{
	NONE,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_STAR,
	KEY_,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
};

#define PCF8574_ADDRESS 0x20

void init_Keypad();
Keys getPressedKey();
int8_t KeysToNumberValue(Keys key);

#endif // MATRIX_KEYPAD_H