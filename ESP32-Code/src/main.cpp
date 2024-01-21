#include <Arduino.h>

#include "TFT.h"
#include "Communication.h"

#define LED_GREEN 2

// Region FunctionDeclaration
void sendRelayOpen(bool open);
// EndRegion FunctionDeclaration

TFT tft; // Create an Instance of the class "TFT"
void setup()
{
	Serial.begin(9600);

	pinMode(LED_GREEN, OUTPUT);

	// Show if esp now is successfully initialized with green led
	digitalWrite(LED_GREEN, initCommunication() == ESP_OK ? HIGH : LOW);

	// Initialize TFT Display
	tft.TFT_Init();
}

void loop()
{
}

void onEspNowCallback(const uint8_t *macAddr, const uint8_t *incomingData, int len)
{
	if (len == 2)
	{
		uint16_t data = (incomingData[0] << 8) + incomingData[1];
		Serial.println(data, HEX);

		// set display value to received poti value
		tft.DisplayValue(data);
	}
}

void sendRelayOpen(bool open)
{
	const uint8_t data = (uint8_t)open;
	if (esp_now_send(receiverAddress, &data, 1) == ESP_OK)
		Serial.println("Send relay open command");
}