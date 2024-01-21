#include "Communication.h"

// Peer to be added
esp_now_peer_info_t receiverPeerInfo;

esp_err_t initCommunication()
{
	esp_err_t err = ESP_OK;
	// Set WiFi mode to station mode (connecting to an access point)
	WiFi.mode(WIFI_STA);

	// Assign new mac-address
	err = esp_wifi_set_mac(WIFI_IF_STA, macAddress);
	if (err != ESP_OK)
		return err;

	// Somehow with the disconnect it works
	// WiFi is sill enabled
	WiFi.disconnect();

	// Initialize esp now
	err = esp_now_init();
	if (err != ESP_OK)
		return err;

	// Set peer configuration
	memcpy(receiverPeerInfo.peer_addr, receiverAddress, 6); // copy mac address to peer info
	receiverPeerInfo.channel = 0;							// set WLAN channel to 0
	receiverPeerInfo.encrypt = false;						// do not encrypt communication

	// Add Esp8266 as communication partner
	esp_now_add_peer(&receiverPeerInfo);

	// Set callback method for esp now
	esp_now_register_recv_cb(onEspNowCallback);
}