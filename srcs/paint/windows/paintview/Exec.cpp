#include "PaintView.hpp"

void    PaintView::execSave(void)
{
    // ...
}

void    PaintView::execCancel(void)
{
    // ...
}

void    PaintView::execBack(void)
{
    // ...
}

void    PaintView::execForward(void)
{
    // ...
}

void    PaintView::execColorSwitch(const Color& newColor)
{
    Color   color = newColor;

    if (color.a < 1)
        color.a = 255;

    updateColor(color);
    updateOpacityFromValue(color.a);
    updateColorText();

    updateCursorImage();
    updateBrushScope();
}
