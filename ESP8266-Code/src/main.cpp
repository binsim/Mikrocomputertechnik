#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

#define POTI_PIN A0
#define RELAY_PIN 0

// const not working with type declaration
uint8_t macAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
uint8_t receiverAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

// Region FunctionDeclaration
void setRelay(bool on);
void sendPotiValue(const int value);
void onEspNowCallback(u8 *mac_addr, u8 *incomingData, u8 len);
// EndRegion FunctionDeclaration

void setup()
{
	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);
	// Setup Relay to be output and off
	pinMode(RELAY_PIN, OUTPUT);
	setRelay(false);

	// Set WiFi mode to station mode (connecting to an access point)
	WiFi.mode(WIFI_STA);

	// set mac address
	wifi_set_macaddr(STATION_IF, receiverAddress);

	WiFi.disconnect();

	Serial.print("MAC-Address: ");
	Serial.println(WiFi.macAddress());

	// LED is active LOW
	digitalWrite(LED_BUILTIN, esp_now_init() == 0 ? LOW : HIGH);

	esp_now_add_peer(macAddress, ESP_NOW_ROLE_COMBO, 0, NULL, 0);
	esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

	// Set callback function for received messages
	esp_now_register_recv_cb(onEspNowCallback);
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

	// // Send data to Esp32 device
	esp_now_send(macAddress, data, 2);
}

void onEspNowCallback(u8 *mac_addr, u8 *incomingData, u8 len)
{
	// TODO: Handle
}
