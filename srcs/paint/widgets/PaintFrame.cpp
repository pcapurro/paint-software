#include "PaintFrame.hpp"

PaintFrame::PaintFrame(const int x, const int y, const int width, \
    const int height, Color& defaultColor, const int selectedTool, \
    const int brushSize, const Color& selectedColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, State::None, false, false})
{
    _pickedColor = _selectedColor;

    _selectedTool = selectedTool;
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

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    _paintTexture.emplace(texture);
    updateTexture();
}

void    PaintFrame::paintBrush(const int x, const int y)
{
    int     newX = x;
    int     newY = y;

    int     r = _brushSize / 2;

    for (int i = 0; i < _brushSize && newY < getHeight(); i++)
    {
        for (int k = 0; k < _brushSize && newX < getWidth() && newY >= 0; k++)
        {
            if (newX >= 0 && _paintData[newY][newX] != _selectedColor)
            {
                int     dx = k - r;
                int     dy = i - r;

                int     dist = ((dx * dx) + (dy * dy));

                if (dist <= r * r)
                    _paintData[newY][newX] = _selectedColor;
            }

            newX++;
        }

        newX = x;
        newY += 1;
    }
}

void    PaintFrame::paintPencil(const int x, const int y)
{
    int     newX = x;
    int     newY = y;

    for (int i = 0; i < _brushSize && newY < getHeight(); i++)
    {
        for (int k = 0; k < _brushSize && newX < getWidth() && newY >= 0; k++)
        {
            if (newX >= 0 && _paintData[newY][newX] != _selectedColor)
                _paintData[newY][newX] = _selectedColor;

            newX++;
        }

        newX = x;
        newY += 1;
    }
}

void    PaintFrame::paintBucket(const int x, const int y)
{
    int         realX = x - getX();
    int         realY = y - getY();

    const int   width = getWidth();
    const int   height = getHeight();

    if (realX < 0 || realX >= (int) width \
        || realY < 0 || realY >= (int) height)
        return;

    if (_paintData[realY][realX] == _selectedColor)
        return;

    vector<std::pair<int, int>>     coords = {{realX, realY}};
    Color                           targetColor = _paintData[realY][realX];

    for (size_t i = 0; i < coords.size(); i++)
    {
        int     xCopy = coords[i].first;
        int     yCopy = coords[i].second;

        while (xCopy > 0 && _paintData[yCopy][xCopy - 1] == targetColor)
            xCopy--;

        while (xCopy < width && _paintData[yCopy][xCopy] == targetColor)
        {
            _paintData[yCopy][xCopy] = _selectedColor;

            if (yCopy - 1 >= 0 && _paintData[yCopy - 1][xCopy] == targetColor)
                coords.emplace_back(xCopy, yCopy - 1);

            if (yCopy + 1 < height && _paintData[yCopy + 1][xCopy] == targetColor)
                coords.emplace_back(xCopy, yCopy + 1);

            xCopy++;
        }
    }
}

void    PaintFrame::paintSpray(const int x, const int y)
{
    (void) x;
    (void) y;

    // ...
}

void    PaintFrame::erase(const int x, const int y)
{
    int     newX = x;
    int     newY = y;

    int     r = _brushSize / 2;

    for (int i = 0; i < _brushSize && newY < getHeight(); i++)
    {
        for (int k = 0; k < _brushSize && newX < getWidth() && newY >= 0; k++)
        {
            if (newX >= 0 && _paintData[newY][newX] != _selectedColor)
            {
                int     dx = k - r;
                int     dy = i - r;

                int     dist = ((dx * dx) + (dy * dy));

                if (dist <= r * r)
                    _paintData[newY][newX].a = 0;
            }

            newX++;
        }

        newX = x;
        newY += 1;
    }
}

void    PaintFrame::pick(const int x, const int y)
{
    if (x < 0 || x >= getWidth())
        return;

    if (y < 0 || y >= getHeight())
        return;

    _pickedColor = _paintData[y][x];
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

Color   PaintFrame::getPickedColor(void) const noexcept
{
    return _pickedColor;
}

void    PaintFrame::setSelectedTool(const int tool)
{
    _selectedTool = tool;
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

    if (_selectedTool == ToolBox::Brush)
        paintBrush(newX, newY);
    else if (_selectedTool == ToolBox::Pencil)
        paintPencil(newX, newY);

    else if (_selectedTool == ToolBox::Bucket)
        paintBucket(x, y);
    else if (_selectedTool == ToolBox::Spray)
        paintSpray(newX, newY);

    else if (_selectedTool == ToolBox::Eraser)
        erase(newX, newY);
    else if (_selectedTool == ToolBox::Picker)
        pick(newX, newY);
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
