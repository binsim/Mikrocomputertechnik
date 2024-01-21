#include <Preferences.h>

class FLashUtil
{
    public:
    void setPin(String pin);
    String getPin();

    private:
    Preferences preferences;
}