#include "TFT.h"

void TFT::TFT_Init()
{
    tft.init();
    tft.setRotation(1);        // Rotates the display by 90 degrees
    tft.fillScreen(TFT_BLACK); // Fill the Backround with Black
    this->analogMeter();

    updateTime = millis();
}

void TFT::DisplayValue(u_int16_t PotiValue)
{
    int value = map(PotiValue, 0, MAX_ANALOG_INPUT_VALUE, 0, 100); // Maps the Value of the Potentiometer for the "plotNeedle" function

    // Updates the Needle after every 35 seconds, which is defined by "LOOP_PERIOD"
    if (updateTime <= millis())
    {
        updateTime = millis() + LOOP_PERIOD;
        this->plotNeedle(value);
    }
}

float TFT::mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void TFT::analogMeter() // Funktion to plot the Basic Analog Meter
{

    // Meter outline
    tft.fillRect(0, 0, M_SIZE * 239, 240, TFT_GREY);
    tft.fillRect(5, 3, M_SIZE * 230, 230, TFT_WHITE);
    tft.drawLine(0, 160, 420, 160, TFT_GREY);

    tft.setTextColor(TFT_BLACK); // Text colour
    tft.drawString("Code:", 10, 170, 4);

    // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
    for (int i = -50; i < 51; i += 5)
    {
        // Long scale tick length
        int tl = 15;

        // Coordinates of tick to draw
        float sx = cos((i - 90) * 0.0174532925);
        float sy = sin((i - 90) * 0.0174532925);
        uint16_t x0 = sx * (M_SIZE * 100 + tl) + M_SIZE * 120;
        uint16_t y0 = sy * (M_SIZE * 100 + tl) + M_SIZE * 140;
        uint16_t x1 = sx * M_SIZE * 100 + M_SIZE * 120;
        uint16_t y1 = sy * M_SIZE * 100 + M_SIZE * 140;

        // Coordinates of next tick for zone fill
        float sx2 = cos((i + 5 - 90) * 0.0174532925);
        float sy2 = sin((i + 5 - 90) * 0.0174532925);
        int x2 = sx2 * (M_SIZE * 100 + tl) + M_SIZE * 120;
        int y2 = sy2 * (M_SIZE * 100 + tl) + M_SIZE * 140;
        int x3 = sx2 * M_SIZE * 100 + M_SIZE * 120;
        int y3 = sy2 * M_SIZE * 100 + M_SIZE * 140;

        // GREEN zone limits
        if (i >= -50 && i < -25)
        {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
        }

        // Yellow zone limits
        if (i >= -25 && i < 0)
        {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
        }

        // Orange zone limits
        if (i >= 0 && i < 25)
        {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
        }

        // Red zone limits
        if (i >= 25 && i < 50)
        {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_RED);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_RED);
        }

        // Short scale tick length
        if (i % 25 != 0)
            tl = 8;

        // Recalculate coords incase tick lenght changed
        x0 = sx * (M_SIZE * 100 + tl) + M_SIZE * 120;
        y0 = sy * (M_SIZE * 100 + tl) + M_SIZE * 140;
        x1 = sx * M_SIZE * 100 + M_SIZE * 120;
        y1 = sy * M_SIZE * 100 + M_SIZE * 140;

        // Draw tick
        tft.drawLine(x0, y0, x1, y1, TFT_BLACK);

        // Check if labels should be drawn, with position tweaks
        if (i % 25 == 0)
        {
            // Calculate label positions
            x0 = sx * (M_SIZE * 100 + tl + 10) + M_SIZE * 120;
            y0 = sy * (M_SIZE * 100 + tl + 10) + M_SIZE * 140;
            switch (i / 25)
            {
            case -2: // at -50 degrees
                tft.drawCentreString("0%", x0, y0 - 12, 2);
                break;
            case -1: // at -25 degrees
                tft.drawCentreString("25%", x0, y0 - 9, 2);
                break;
            case 0: // at 0 degrees
                tft.drawCentreString("50%", x0, y0 - 7, 2);
                break;
            case 1: // at 25 degrees
                tft.drawCentreString("75%", x0, y0 - 9, 2);
                break;
            case 2: // at 50 degrees
                tft.drawCentreString("100%", x0, y0 - 12, 2);
                break;
            }
        }

        // Now draw the arc of the scale
        sx = cos((i + 5 - 90) * 0.0174532925);
        sy = sin((i + 5 - 90) * 0.0174532925);
        x0 = sx * M_SIZE * 100 + M_SIZE * 120;
        y0 = sy * M_SIZE * 100 + M_SIZE * 140;
        // Draw scale arc, don't draw the last part
        if (i < 50)
            tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
    }

    tft.drawCentreString("Poti Value", M_SIZE * 120, M_SIZE * 70, 4); // Draw Center "Poti Value" in the Middle of the Screen

    plotNeedle(0); // Put meter needle at 0
}

void TFT::plotNeedle(int value)
{
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    String RightString = String(this->mapFloat(value, 0, 100, 0, 3.3)) + "V";
    tft.drawRightString(RightString, 50, 120, 2);

    if (value < -10)
        value = -10; // Limit value to emulate needle end stops
    if (value > 110)
        value = 110;

    // Move the needle until new value reached

    old_analog = value; // Update immediately if delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calculate tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(M_SIZE * (120 + 20 * ltx - 1), M_SIZE * (140 - 20), osx - 1, osy, TFT_WHITE);
    tft.drawLine(M_SIZE * (120 + 20 * ltx), M_SIZE * (140 - 20), osx, osy, TFT_WHITE);
    tft.drawLine(M_SIZE * (120 + 20 * ltx + 1), M_SIZE * (140 - 20), osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    tft.setTextColor(TFT_BLACK);
    tft.drawCentreString("Poti Value", M_SIZE * 120, M_SIZE * 70, 4);

    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE * (sx * 98 + 120);
    osy = M_SIZE * (sy * 98 + 140);

    // draws 3 lines to thicken needle
    tft.drawLine(M_SIZE * (120 + 20 * ltx - 1), M_SIZE * (140 - 20), osx - 1, osy, TFT_RED);
    tft.drawLine(M_SIZE * (120 + 20 * ltx), M_SIZE * (140 - 20), osx, osy, TFT_MAGENTA);
    tft.drawLine(M_SIZE * (120 + 20 * ltx + 1), M_SIZE * (140 - 20), osx + 1, osy, TFT_RED);
}

void TFT::updatePin(String Input_Pin)
{
    tft.fillRect(90, 165, 220, 30, TFT_WHITE); // Erase old code
    String DisplayString = "";
    if (Input_Pin.length() == 0) // Return when String is empty
        return;

    for (int i = 0; i < Input_Pin.length() - 1; i++) // Set "*" for every char in the String exepct the last one
    {
        DisplayString += "*";
    }

    DisplayString += Input_Pin.charAt(Input_Pin.length() - 1); // Add last char of the String

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString(DisplayString, 90, 170, 4); // Display String
}