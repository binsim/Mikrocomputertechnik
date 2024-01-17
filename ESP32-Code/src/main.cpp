#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>

void onEspNowCallback(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

void setup()
{
	Serial.print("MAC-Address: ");
	Serial.println(WiFi.macAddress());

	esp_now_register_recv_cb(onEspNowCallback);
}

void loop()
{
}

void onEspNowCallback(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
{
}