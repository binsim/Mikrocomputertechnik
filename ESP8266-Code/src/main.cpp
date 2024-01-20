#include <Arduino.h>

#include "Communication.h"

#define POTI_PIN A0
#define RELAY_PIN 0

// Region FunctionDeclaration
void setRelay(bool on);
void sendPotiValue(const int value);
// EndRegion FunctionDeclaration

void setup()
{
	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);
	// Setup Relay to be output and off
	pinMode(RELAY_PIN, OUTPUT);
	setRelay(false);

	// LED is active LOW
	digitalWrite(LED_BUILTIN, initCommunication() == 0 ? LOW : HIGH);
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

			// Send value to ESP32
			sendPotiValue(potiValue);

			prevPotiValue = potiValue;
		}
	}
}

void setRelay(bool on)
{
	digitalWrite(RELAY_PIN, on ? HIGH : LOW);
}

void sendPotiValue(int value)
{
	u8 data[] = {(value >> 8) & 0xFF, value & 0xFF};

	Serial.print("Send poti value: ");
	Serial.print(data[0], HEX);
	Serial.print(data[1], HEX);

	// // Send data to Esp32 device
	esp_now_send(macAddress, data, 2);
}

void onEspNowCallback(u8 *mac_addr, u8 *incomingData, u8 len)
{
	// TODO: Handle
}
