#include <Arduino.h>

#define POTI_PIN A0
#define RELAY_PIN 0

// Region FunctionDeclaration
void setRelay(bool on);
// EndRegion FunctionDeclaration

void setup()
{
	Serial.begin(9600);

	// Setup Relay to be output and off
	pinMode(RELAY_PIN, OUTPUT);
	setRelay(false);
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

void setRelay(bool on)
{
	digitalWrite(RELAY_PIN, on ? HIGH : LOW);
}