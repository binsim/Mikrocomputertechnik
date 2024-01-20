#include <Preferences.h>

class FLashUtil
{
    public:
    void setConfigured(bool configured);
    bool getConfigured();

    void setPin(String pin);
    String getPin();

    private:
    Preferences preferences;
}