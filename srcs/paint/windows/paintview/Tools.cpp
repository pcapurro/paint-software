#include "PaintView.hpp"

Color   PaintView::generateRandomColor(void) const noexcept
{
    unsigned char   r = rand() % 256;
    unsigned char   g = rand() % 256;
    unsigned char   b = rand() % 256;

    return {r, g, b, 255};
}
