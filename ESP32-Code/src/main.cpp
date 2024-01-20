#include <Arduino.h>

#include "FlashUtil.h"

FlashUtil flashUtil;

void setup()
{
    Serial.begin(115200); //open serial port
    delay(100); //wait for PC to open serial port

    Serial.println("###################################  STARTUP ################################");

    if(!flashUtil.getConfigured())
    {
        Serial.println("No pin has been configured yet. Please configure a pin first.");
    }
    
    //TODO: add code here

    Serial.println("###################################  Setup Done!!! ################################");
}

void loop()
{
}
