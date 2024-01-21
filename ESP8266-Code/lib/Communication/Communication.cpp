#include "Communication.h"

int initCommunication()
{
	int err = 0;
	// Set WiFi mode to station mode (connecting to an access point)
	WiFi.mode(WIFI_STA);

	// set mac address
	wifi_set_macaddr(STATION_IF, const_cast<uint8_t *>(receiverAddress));

	// Somehow with the disconnect it works
	// WiFi is sill enabled
	WiFi.disconnect();

	// Initialize esp now
	err = esp_now_init();
	if (err != 0)
		return err;

	// Add ESP32 as peer
	esp_now_add_peer(const_cast<u8 *>(macAddress), ESP_NOW_ROLE_COMBO, 0, NULL, 0);
	esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

	// Set callback function for received messages
	err = esp_now_register_recv_cb(onEspNowCallback);
	if (err != 0)
		return err;

	return err;
}