#include "MatrixKeypad.h"

void init_Keypad()
{
	Wire.begin(21, 22);
}

char getPressedKey()
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
				return '1';
			case 0xED:
				return '2';
			case 0xEB:
				return '3';
			case 0xE7:
				return 'A';

			case 0xDE:
				return '4';
			case 0xDD:
				return '5';
			case 0xDB:
				return '6';
			case 0xD7:
				return 'B';

			case 0xBE:
				return '7';
			case 0xBD:
				return '8';
			case 0xBB:
				return '9';
			case 0xB7:
				return 'C';

			case 0x7E:
				return '*';
			case 0x7D:
				return '0';
			case 0x7B:
				return '#';
			case 0x77:
				return 'D';

			default:
				Serial1.print("Received data: ");
				Serial.println(data, HEX);
				break;
			}
		}
	}

	return 0;
}
