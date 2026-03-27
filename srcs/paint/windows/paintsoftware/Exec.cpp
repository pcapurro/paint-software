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

void    PaintSoftware::execColorSwitch(const Color& newColor)
{
    Color   color = newColor;

    if (color.a < 1)
        color.a = 255;

    updateColor(color);
    updateOpacityFromValue(color.a);
}
