#include "PaintFrame.hpp"

PaintFrame::PaintFrame(const int x, const int y, const int width, \
    const int height, Color& defaultColor) : \
        Element({x, y, width, height}), \
        _frame(x, y, width, height, defaultColor)
{
    ;
}
