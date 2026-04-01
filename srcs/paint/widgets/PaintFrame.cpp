#include "PaintFrame.hpp"

PaintFrame::PaintFrame(const int x, const int y, const int width, \
    const int height, Color& defaultColor) : \
        Element({x, y, width, height}, {}, {false, false, true, SDL_SYSTEM_CURSOR_CROSSHAIR, false, false}), \
        _frame(x, y, width, height, defaultColor)
{
    initPngBack();

    // ...
}

void    PaintFrame::initPngBack(void)
{
    const int   nbW = (getWidth() / PngWidth);
    const int   nbH = (getHeight() / PngHeight);

    int         pngX = getX();
    int         pngY = getY();

    _pngBack.reserve(((nbW * nbH) / 2) + 1);

    _pngBack.emplace_back(pngX, pngY, getWidth(), \
        getHeight(), Color::GreyDark);

    for (int i = 0; i < nbH; i++)
    {
        for (int k = 0; k < nbW; k++)
        {
            if ((k + i) % 2 != 0)
                _pngBack.emplace_back(pngX, pngY, PngWidth, PngHeight, Color::GreyLight);

            pngX += PngWidth;
        }

        pngX = getX();
        pngY += PngHeight;
    }
}

void    PaintFrame::render(SDL_Renderer* renderer)
{
    for (auto& png : _pngBack)
        png.render(renderer);

    _frame.render(renderer);

    // ...
}

void	PaintFrame::onMouseDown(const int /*x*/, const int /*y*/, \
	SDL_Renderer* /*renderer*/)
{
	// ...
}

void	PaintFrame::onMouseUp(const int /*x*/, const int /*y*/, \
	SDL_Renderer* /*renderer*/)
{
	// ...
}

void	PaintFrame::onMouseHover(const int /*x*/, const int /*y*/, \
	SDL_Renderer* /*renderer*/)
{
	setHover(true);
}

void	PaintFrame::onMouseHoverOutside(SDL_Renderer* /*renderer*/)
{
    setHover(false);
}
