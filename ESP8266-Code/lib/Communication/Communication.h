#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

// const not working for this libary
const uint8_t macAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
const uint8_t receiverAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

// This function must be declared by the user
void onEspNowCallback(u8 *mac_addr, u8 *incomingData, u8 len);

int initCommunication();

#endif // COMMUNICATION_H