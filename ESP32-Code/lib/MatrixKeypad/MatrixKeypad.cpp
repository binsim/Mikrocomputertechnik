#include "MatrixKeypad.h"

void init_Keypad()
{
	Wire.begin(21, 22);

	Wire.beginTransmission(PCF8574_ADDRESS);
	Wire.write(0x1F);
	Wire.endTransmission();
}

Keys getPressedKey()
{
	for (char row = 0; row < 4; row++)
	{
		// Send command to set row pin to 0
		Wire.beginTransmission(PCF8574_ADDRESS);
		Wire.write(0xFF & ~(1 << (4 + row)));
		Wire.endTransmission();

		// Check for pressed key in row
		Wire.requestFrom(PCF8574_ADDRESS, 1);
		if (!Wire.available())
			continue;

		char data = Wire.read();
		if ((data & 0x0F) != 0b1111)
		{
			switch (data)
			{
			case 0xEE:
				return KEY_1;
			case 0xED:
				return KEY_2;
			case 0xEB:
				return KEY_3;
			case 0xE7:
				return KEY_A;

			case 0xDE:
				return KEY_4;
			case 0xDD:
				return KEY_5;
			case 0xDB:
				return KEY_6;
			case 0xD7:
				return KEY_B;

			case 0xBE:
				return KEY_7;
			case 0xBD:
				return KEY_8;
			case 0xBB:
				return KEY_9;
			case 0xB7:
				return KEY_C;

			case 0x7E:
				return KEY_STAR;
			case 0x7D:
				return KEY_0;
			case 0x7B:
				return KEY_;
			case 0x77:
				return KEY_D;

			default:
				Serial1.print("Received data: ");
				Serial.println(data, HEX);
				break;
			}
		}
	}

	return NONE;
}