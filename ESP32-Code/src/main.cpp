#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include "TFT.h"

const uint8_t macAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
const uint8_t receiverAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

#define LED_GREEN 2

void onEspNowCallback(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

TFT tft; // Create an Instance of the class "TFT"
esp_now_peer_info_t receiverPeerInfo;
void setup()
{
	Serial.begin(9600);

	pinMode(LED_GREEN, OUTPUT);

	// Set WiFi mode to station mode (connecting to an access point)
	WiFi.mode(WIFI_STA);
	// Assign new mac-address
	esp_wifi_set_mac(WIFI_IF_STA, macAddress);

	WiFi.disconnect();

	Serial.print("MAC-Address: ");
	Serial.println(WiFi.macAddress());

	// Show if esp now is successfully initialized with green led
	digitalWrite(LED_GREEN, esp_now_init() == ESP_OK ? HIGH : LOW);

	// Set peer configuration
	memcpy(receiverPeerInfo.peer_addr, receiverAddress, 6); // copy mac address to peer info
	receiverPeerInfo.channel = 0;							// set WLAN channel to 0
	receiverPeerInfo.encrypt = false;						// do not encrypt communication

	// Add Esp8266 as communication partner
	esp_now_add_peer(&receiverPeerInfo);

	// Set callback method for esp now
	esp_now_register_recv_cb(onEspNowCallback);

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