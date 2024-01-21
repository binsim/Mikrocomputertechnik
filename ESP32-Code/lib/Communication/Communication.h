#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>

// MAC-Address of the ESP32-Board
const uint8_t macAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
// MAC-Address of the ESP8266-Board
const uint8_t receiverAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

// This function must be declared by the user
void onEspNowCallback(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

// Function to be added into the setup
// Initialises all necessary things for esp now communication
esp_err_t initCommunication();

#endif // COMMUNICATION_H