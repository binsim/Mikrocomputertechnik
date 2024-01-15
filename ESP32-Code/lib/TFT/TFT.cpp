#include "TFT.h"

void TFT::TFT_Init()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    this->analogMeter();

    updateTime = millis();
}

void TFT::DisplayValue(int value)
{
    value = map(value, 0, MAX_ANALOG_INPUT, 0, 100);

    if (updateTime <= millis())
    {
        updateTime = millis() + LOOP_PERIOD;
        this->plotNeedle(value, 0);
    }
}

void TFT::analogMeter()
{
    // Meter outline
    tft.fillRect(0, 0, 239, 126, TFT_GREY);
    tft.fillRect(5, 3, 230, 119, TFT_WHITE);

    tft.setTextColor(TFT_BLACK); // Text colour

    // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
    for (int i = -50; i < 51; i += 5)
    {
        // Long scale tick length
        int tl = 15;

        // Coordinates of tick to draw
        float sx = cos((i - 90) * 0.0174532925);
        float sy = sin((i - 90) * 0.0174532925);
        uint16_t x0 = sx * (100 + tl) + 120;
        uint16_t y0 = sy * (100 + tl) + 140;
        uint16_t x1 = sx * 100 + 120;
        uint16_t y1 = sy * 100 + 140;

        // Coordinates of next tick for zone fill
        float sx2 = cos((i + 5 - 90) * 0.0174532925);
        float sy2 = sin((i + 5 - 90) * 0.0174532925);
        int x2 = sx2 * (100 + tl) + 120;
        int y2 = sy2 * (100 + tl) + 140;
        int x3 = sx2 * 100 + 120;
        int y3 = sy2 * 100 + 140;

        // Yellow zone limits
        // if (i >= -50 && i < 0) {
        //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
        //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
        //}

        // Green zone limits
        if (i >= 0 && i < 25)
        {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
        }

        // Orange zone limits
        if (i >= 25 && i < 50)
        {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
        }

        // Short scale tick length
        if (i % 25 != 0)
            tl = 8;

        // Recalculate coords incase tick lenght changed
        x0 = sx * (100 + tl) + 120;
        y0 = sy * (100 + tl) + 140;
        x1 = sx * 100 + 120;
        y1 = sy * 100 + 140;

        // Draw tick
        tft.drawLine(x0, y0, x1, y1, TFT_BLACK);

        // Check if labels should be drawn, with position tweaks
        if (i % 25 == 0)
        {
            // Calculate label positions
            x0 = sx * (100 + tl + 10) + 120;
            y0 = sy * (100 + tl + 10) + 140;
            switch (i / 25)
            {
            case -2:
                tft.drawCentreString("0%", x0, y0 - 12, 2);
                break;
            case -1:
                tft.drawCentreString("25%", x0, y0 - 9, 2);
                break;
            case 0:
                tft.drawCentreString("50%", x0, y0 - 6, 2);
                break;
            case 1:
                tft.drawCentreString("75%", x0, y0 - 9, 2);
                break;
            case 2:
                tft.drawCentreString("100%", x0, y0 - 12, 2);
                break;
            }
        }

        // Now draw the arc of the scale
        sx = cos((i + 5 - 90) * 0.0174532925);
        sy = sin((i + 5 - 90) * 0.0174532925);
        x0 = sx * 100 + 120;
        y0 = sy * 100 + 140;
        // Draw scale arc, don't draw the last part
        if (i < 50)
            tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
    }

    tft.drawCentreString("Poti Value", 120, 70, 4); // Comment out to avoid font 4
    tft.drawRect(5, 3, 230, 119, TFT_BLACK);        // Draw bezel line

    plotNeedle(0, 0); // Put meter needle at 0
}

void TFT::plotNeedle(int value, byte ms_delay)
{
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    // char buf[8];
    // dtostrf(value, 4, 0, buf);
    String RightString = String(this->mapFloat(value, 0, 100, 0, 3.3)) + "V";
    tft.drawRightString(RightString, 50, 119 - 20, 2);

    if (value < -10)
        value = -10; // Limit value to emulate needle end stops
    if (value > 110)
        value = 110;

    // Move the needle util new value reached
    while (!(value == old_analog))
    {
        if (old_analog < value)
            old_analog++;
        else
            old_analog--;

        if (ms_delay == 0)
            old_analog = value; // Update immediately id delay is 0

        float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
        // Calculate tip of needle coords
        float sx = cos(sdeg * 0.0174532925);
        float sy = sin(sdeg * 0.0174532925);

        // Calculate x delta of needle start (does not start at pivot point)
        float tx = tan((sdeg + 90) * 0.0174532925);

        // Erase old needle image
        tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_WHITE);
        tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_WHITE);
        tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_WHITE);

        // Re-plot text under needle
        tft.setTextColor(TFT_BLACK);
        tft.drawCentreString("Poti Value", 120, 70, 4); // // Comment out to avoid font 4

        // Store new needle end coords for next erase
        ltx = tx;
        osx = sx * 98 + 120;
        osy = sy * 98 + 140;

        // Draw the needle in the new postion, magenta makes needle a bit bolder
        // draws 3 lines to thicken needle
        tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_RED);
        tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_MAGENTA);
        tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_RED);

        // Slow needle down slightly as it approaches new postion
        if (abs(old_analog - value) < 10)
            ms_delay += ms_delay / 5;

        // Wait before next update
        delay(ms_delay);
    }
}

float TFT::mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}