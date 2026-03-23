#include "PaintSoftware.hpp"

void    PaintSoftware::execSave(void)
{
    // ...
}

void    PaintSoftware::execCancel(void)
{
    // ...
}

void    PaintSoftware::execBack(void)
{
    // ...
}

void    PaintSoftware::execForward(void)
{
    // ...
}

void    PaintSoftware::execColorSwitch(void)
{
    ColorSelection  window("paint-software – color selection", "materials/font/OpenSans.ttf", \
        400, 170, LIGHT_MODE, "Color selection", true, "Select a brush a color.");

    window.routine();

    Color           newColor;
    vector<uint8_t> values = window.getFinalValues();

    newColor.r = values[0];
    newColor.g = values[1];
    newColor.b = values[2];

    newColor.a = values[3];

    if (newColor.a < 1)
        newColor.a = 255;

    updateColor(newColor);

    updateOpacityFromValue(newColor.a);
}
