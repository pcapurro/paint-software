#include "PaintFrame.hpp"

PaintFrame::PaintFrame(const int x, const int y, const int width, \
    const int height, Color& defaultColor) : \
        Element({x, y, width, height}), \
        _frame(x, y, width, height, defaultColor)
{
    initPngBack();

    // ...
}

void    PaintFrame::initPngBack(void)
{
    const int   nbW = (getWidth() / PNG_W);
    const int   nbH = (getHeight() / PNG_H);

    int         pngX = getX();
    int         pngY = getY();

    Color       pngColor = LIGHT_GREY;
    Color       darkGrey = DARK_GREY;

    _pngBack.reserve(((nbW * nbH) / 2) + 1);

    _pngBack.emplace_back(pngX, pngY, getWidth(), \
        getHeight(), darkGrey);

    for (int i = 0; i < nbH; i++)
    {
        for (int k = 0; k < nbW; k++)
        {
            if ((k + i) % 2 != 0)
                _pngBack.emplace_back(pngX, pngY, PNG_W, PNG_H, pngColor);

            pngX += PNG_W;
        }

        pngX = getX();
        pngY += PNG_H;
    }
}

void    PaintFrame::render(SDL_Renderer* renderer)
{
    for (auto& png : _pngBack)
        png.render(renderer);

    _frame.render(renderer);

    // ...
}
