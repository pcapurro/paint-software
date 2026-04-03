#include "PaintFrame.hpp"

PaintFrame::PaintFrame(const int x, const int y, const int width, \
    const int height, Color& defaultColor, const int brushSize, \
    const Color& selectedColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
    _brushSize = brushSize;
    _selectedColor = selectedColor;

    initPngBack();

    initPaintData(defaultColor);
    initPaintTexture(renderer);
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

void    PaintFrame::initPaintData(const Color& defaultColor)
{
    _paintData.resize(getHeight());

    for (int i = 0; i < getHeight(); i++)
        _paintData[i].insert(_paintData[i].end(), getWidth(), defaultColor);
}

void    PaintFrame::initPaintTexture(SDL_Renderer* renderer)
{
    SDL_Texture*    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, \
        SDL_TEXTUREACCESS_STREAMING, getWidth(), getHeight());

    if (!texture)
    {
		throw std::runtime_error("SDL failed to create a painting texture (" \
			+ string(SDL_GetError()) + ").");
    }

    _paintTexture.emplace(texture);
    updateTexture();
}

void    PaintFrame::paint(const int x, const int y, \
    const int brushSize, const Color& color)
{
    int     newX = x;
    int     newY = y;

    for (int i = 0; i < brushSize && newY < getHeight(); i++)
    {
        for (int k = 0; k < brushSize && newX < getWidth() && newY >= 0; k++)
        {
            if (newX >= 0 && _paintData[newY][newX] != color)
                _paintData[newY][newX] = color;

            newX++;
        }

        newX = x;
        newY += 1;
    }
}

void    PaintFrame::updateTexture(void)
{
    SDL_Texture*            texture = _paintTexture->getTexture();
    const SDL_PixelFormat*  format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    vector<Uint32>          paint;
    Uint32                  pixel;

    paint.reserve(getWidth() * getHeight());

    for (int y = 0; y < (int) _paintData.size(); y++)
    {
        for (int x = 0; x < (int) _paintData[y].size(); x++)
        {
            pixel = _paintData[y][x].toUint32t(format);
            paint.push_back(pixel);
        }
    }

    SDL_UpdateTexture(texture, nullptr, paint.data(), \
        getWidth() * sizeof(Uint32));
}

void    PaintFrame::render(SDL_Renderer* renderer)
{
    for (auto& png : _pngBack)
        png.render(renderer);

    updateTexture();

    SDL_Rect    main {getX(), getY(), getWidth(), getHeight()};

    SDL_RenderCopy(renderer, _paintTexture->getTexture(), \
        nullptr, &main);

    // ...
}

void    PaintFrame::setBrushSize(const int newBrushSize)
{
    _brushSize = newBrushSize;
}

void    PaintFrame::setSelectedColor(const Color& newColor)
{
    _selectedColor = newColor;
}

void	PaintFrame::onMouseDown(const int x, const int y, \
	SDL_Renderer* /*renderer*/)
{
    int     newX = (x - getX()) - (_brushSize / 2);
    int     newY = (y - getY()) - (_brushSize / 2);

    paint(newX, newY, _brushSize, _selectedColor);
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
