#include "PaintView.hpp"

void    PaintView::execCancel(void)
{
    _paintFrame->clear();
}

void    PaintView::execBack(void)
{
    _paintFrame->back();
}

void    PaintView::execForward(void)
{
    _paintFrame->forward();
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
