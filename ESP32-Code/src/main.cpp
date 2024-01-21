#include <Arduino.h>

#include "FlashUtil.h"

FlashUtil flashUtil;

void setup()
{
    Serial.begin(115200); //open serial port
    delay(100); //wait for PC to open serial port

    Serial.println("###################################  STARTUP ################################");

    
    //TODO: add code here

    Serial.println("###################################  Setup Done!!! ################################");
}

void loop()
{
}
