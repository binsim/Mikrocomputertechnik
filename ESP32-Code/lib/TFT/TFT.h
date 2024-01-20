#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#define TFT_GREY 0x5AEB

#define LOOP_PERIOD 35              // Display updates every 35 ms
#define MAX_ANALOG_INPUT_VALUE 4095 // Max Input Value of the Potentiometer
#define M_SIZE 1.3333               // Factor to scale the Analog Meter over the whole TFT

class TFT
{
public:
    void TFT_Init();
    void DisplayValue(u_int16_t value);

private:
    TFT_eSPI tft = TFT_eSPI();
    float ltx = 0;                 // Saved x coord of bottom of needle
    uint16_t osx = 120, osy = 120; // Saved x & y coords
    uint32_t updateTime = 0;       // time for next update

    int old_analog = -999; // Value last displayed

    void analogMeter();
    void plotNeedle(int value, byte ms_delay);
    float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
};