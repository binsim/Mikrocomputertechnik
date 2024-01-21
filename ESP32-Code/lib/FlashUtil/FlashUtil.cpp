#include "FlashUtil.h"

Preferences preferences;

void setPin(String pin)
{
    preferences.begin("lock", false); // start preferences with namespace "schloss" and read/write pernission

    if (pin != preferences.getString("pin", "")) // check if pin is different to avoid unnecessary writes
    {
        preferences.putString("pin", pin); // save pin
    }

    preferences.end(); // close preferences
}

String getPin()
{
    String pinTemp;

    preferences.begin("lock", true);            // start preferences with namespace "schloss" and read pernission
    pinTemp = preferences.getString("pin", ""); // read pin
    preferences.end();                          // close preferences
    return pinTemp;
}