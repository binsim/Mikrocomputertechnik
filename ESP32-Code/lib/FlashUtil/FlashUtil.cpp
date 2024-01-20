#include "FlashUtil.h"

void FlashUtil::setConfigured(bool configured)
{
    preferences.begin("schloss", false); // start preferences with namespace "schloss" and read/write pernission
    preferences.putBool("configured", configured); //save configured
	preferences.end(); // close preferences
}

bool FlashUtil::getConfigured()
{
    bool configTemp;

    preferences.begin("schloss", true); // start preferences with namespace "schloss" and read pernission
    configTemp = preferences.getBool("configured", false); //read configured
    preferences.end(); // close preferences
    return configTemp;
}

void FlashUtil::setPin(String pin)
{
    preferences.begin("schloss", false); // start preferences with namespace "schloss" and read/write pernission
    preferences.putString("pin", pin); //save pin
    preferences.end(); // close preferences
}

String FlashUtil::getPin()
{	
    String pinTemp;

    preferences.begin("schloss", true); // start preferences with namespace "schloss" and read pernission
    pinTemp = preferences.getString("pin", false); //read pin
    preferences.end(); // close preferences
    return pinTemp;
}