#include <Preferences.h>

class FlashUtil
{
public:
    void setPin(String pin);
    String getPin();

private:
    Preferences preferences;
};