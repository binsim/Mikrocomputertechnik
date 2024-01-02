#include <Arduino.h>

#define POTI_PIN A0

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// ############################################ READING POTI ######################################################
	{
		// TODO: Smooth out values

		// Saving previously read values
		static int prevPotiValue = 0;
		// Read value from Poti
		int potiValue = analogRead(POTI_PIN);
		if (potiValue != prevPotiValue)
		{
			Serial.print("Poti value changed: ");
			Serial.println(potiValue);

			// TODO: Send value to ESP32

			prevPotiValue = potiValue;
		}
	}
}
