#include "PaintFrame.hpp"

PaintFrame::PaintFrame(const int x, const int y, const int width, \
    const int height, const int selectedTool, const int brushSize, \
    const Color& selectedColor, const int displayMode, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, State::None, false, false}) , \
        _displayMode(displayMode)
{
    _pickedColor = _selectedColor;

    _selectedTool = selectedTool;
    _brushSize = brushSize;
    _selectedColor = selectedColor;

    initPngBack();

    initPaintData();
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

void    PaintFrame::initPaintData(void)
{
    _paintData.resize(getHeight());

    for (int i = 0; i < getHeight(); i++)
        _paintData[i].insert(_paintData[i].end(), getWidth(), Color::White);
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

    for (int i = 0; i < _brushSize && newY < getHeight(); i++, newY++)
    {
        for (int k = 0; k < _brushSize && newX < getWidth() && newY >= 0; k++, newX++)
        {
            if (newX < 0 || _paintData[newY][newX] == _selectedColor)
                continue;

            int     dx = k - r;
            int     dy = i - r;

            int     dist = ((dx * dx) + (dy * dy));

            if (dist <= r * r)
                _paintData[newY][newX] = _selectedColor;
        }

        newX = x;
    }
}

void    PaintFrame::paintPencil(const int x, const int y)
{
    int     newX = x;
    int     newY = y;

    for (int i = 0; i < _brushSize && newY < getHeight(); i++, newY++)
    {
        for (int k = 0; k < _brushSize && newX < getWidth() && newY >= 0; k++, newX++)
        {
            if (newX >= 0 && _paintData[newY][newX] != _selectedColor)
                _paintData[newY][newX] = _selectedColor;
        }

        newX = x;
    }
}

void    PaintFrame::paintBucket(const int x, const int y)
{
    const int   width = getWidth();
    const int   height = getHeight();

    if (x < 0 || x >= (int) width \
        || y < 0 || y >= (int) height)
        return;

    if (_paintData[y][x] == _selectedColor)
        return;

    vector<std::pair<int, int>>     coords = {{x, y}};
    Color                           targetColor = _paintData[y][x];

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
    int     newX = x;
    int     newY = y;

    int     r = _brushSize / 2;

    for (int i = 0; i < _brushSize && newY < getHeight(); i++, newY++)
    {
        for (int k = 0; k < _brushSize && newX < getWidth() && newY >= 0; k++, newX++)
        {
            if (newX < 0)
                continue;

            int     dx = k - r;
            int     dy = i - r;

            int     dist = ((dx * dx) + (dy * dy));

            if (dist <= r * r)
            {
                float   ratio = std::sqrt(dist) / r;

                if ((ratio <= 0.33f && rand() % 4 == 0) || rand() % 7 == 0)
                    _paintData[newY][newX] = _selectedColor;
            }
        }

        newX = x;
    }
}

void    PaintFrame::erase(const int x, const int y)
{
    int     newX = x;
    int     newY = y;

    int     r = _brushSize / 2;

    for (int i = 0; i < _brushSize && newY < getHeight(); i++, newY++)
    {
        for (int k = 0; k < _brushSize && newX < getWidth() && newY >= 0; k++, newX++)
        {
            if (newX < 0 || _paintData[newY][newX].a == 0)
                continue;

            int     dx = k - r;
            int     dy = i - r;

            int     dist = ((dx * dx) + (dy * dy));

            if (dist <= r * r)
                _paintData[newY][newX].a = 0;
        }

        newX = x;
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

void    PaintFrame::paintLine(const int endX, const int endY)
{
    int     initX = _lineStart.first;
    int     initY = _lineStart.second;

    int     finalX = endX;
    int     finalY = endY;

    if (initX == -1 || initY == -1 \
        || initX == finalX || initY == finalY)
    {
        _lineStart = { -1, -1 };
        _lineEnd = { -1, -1 };

        return;
    }

    int     distX = finalX - initX;
    int     distY = finalY - initY;

    int     maxDist = std::max(std::abs(distX), std::abs(distY));

    float   deltaX = (float) distX / maxDist;
    float   deltaY = (float) distY / maxDist;

    for (int i = 0; i <= maxDist; i++)
    {
        int     x = (int) (initX + deltaX * i);
        int     y = (int) (initY + deltaY * i);

        if (x < getWidth() && y < getHeight() \
            && x >= 0 && y >= 0)
            _paintData[y][x] = _selectedColor;
    }

    _lineStart = { -1, -1 };
    _lineEnd = { -1, -1 };
}

void    PaintFrame::paintRectangle(const int endX, const int endY)
{
    int     initX = _rectStart.first;
    int     initY = _rectStart.second;

    int     finalX = endX;
    int     finalY = endY;

    if (initX == -1 || initY == -1 \
        || initX == finalX || initY == finalY)
    {
        _rectStart = { -1, -1 };
        _rectEnd = { -1, -1 };

        return;
    }

    if (initX > finalX)
        std::swap(initX, finalX);
    if (initY > finalY)
        std::swap(initY, finalY);

    for (int x = initX; x <= finalX; x++)
    {
        if (x >= getWidth())
            break;

        if (initY < getHeight())
            _paintData[initY][x] = _selectedColor;
        if (finalY < getHeight())
            _paintData[finalY][x] = _selectedColor;
    }

    for (int y = initY; y <= finalY; y++)
    {
        if (y >= getHeight())
            break;

        if (initX < getWidth())
            _paintData[y][initX] = _selectedColor;
        if (finalX < getWidth())
            _paintData[y][finalX] = _selectedColor;
    }

    for (int y = initY + 1; y < finalY; y++)
    {
        for (int x = initX + 1; x < finalX; x++)
            _paintData[y][x] = _selectedColor;
    }

    _rectStart = { -1, -1 };
    _rectEnd = { -1, -1 };
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
    if (_displayMode == Window::LightMode)
    {
        SDL_Rect    main {getX() - 1, getY() - 1, \
            getWidth() + 2, getHeight() + 2};

        SDL_SetRenderDrawColor(renderer, Color::Black.r, Color::Black.g, \
            Color::Black.b, Color::Black.a);

        SDL_RenderDrawRect(renderer, &main);
    }

    for (auto& png : _pngBack)
        png.render(renderer);

    updateTexture();

    SDL_Rect    main {getX(), getY(), getWidth(), getHeight()};

    SDL_RenderCopy(renderer, _paintTexture->getTexture(), \
        nullptr, &main);

    if (_selectedTool == ToolBox::Line
        && _lineStart != std::pair{ -1, -1 } && _lineEnd != std::pair{ -1, -1 })
    {
        SDL_SetRenderDrawColor(renderer, _selectedColor.r, _selectedColor.g, \
            _selectedColor.b, _selectedColor.a);

        SDL_RenderDrawLine(renderer, getX() + _lineStart.first, getY() + _lineStart.second, \
            getX() + _lineEnd.first, getY() + _lineEnd.second);
    }

    else if (_selectedTool == ToolBox::Rectangle
        && _rectStart != std::pair{ -1, -1 } && _rectEnd != std::pair{ -1, -1 })
    {
        main = { getX() + _rectStart.first, getY() + _rectStart.second, \
            (getX() + _rectEnd.first) - (getX() + _rectStart.first), \
            (getY() + _rectEnd.second) - (getY() + _rectStart.second) };

        SDL_SetRenderDrawColor(renderer, _selectedColor.r, _selectedColor.g, \
            _selectedColor.b, _selectedColor.a);

        SDL_RenderDrawRect(renderer, &main);
    }
}

void    PaintFrame::clear(void)
{
    _paintData.clear();

    initPaintData();
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

void	PaintFrame::onMouseDown(const bool held, const int x, \
    const int y, SDL_Renderer* /*renderer*/)
{
    int     centerX = x - getX();
    int     centerY = y - getY();

    int     newX = centerX - (_brushSize / 2);
    int     newY = centerY - (_brushSize / 2);

    if (_selectedTool == ToolBox::Brush)
        paintBrush(newX, newY);
    else if (_selectedTool == ToolBox::Pencil)
        paintPencil(newX, newY);

    else if (_selectedTool == ToolBox::Bucket)
        paintBucket(centerX, centerY);
    else if (_selectedTool == ToolBox::Spray)
        paintSpray(newX, newY);

    else if (_selectedTool == ToolBox::Eraser)
        erase(newX, newY);
    else if (_selectedTool == ToolBox::Picker)
        pick(newX, newY);

    else if (_selectedTool == ToolBox::Line)
    {
        if (!held)
            _lineStart = { centerX, centerY };
    }
    else if (_selectedTool == ToolBox::Rectangle)
    {
        if (!held)
            _rectStart = { centerX, centerY };
    }
}

void	PaintFrame::onMouseUp(const int x, const int y, \
	SDL_Renderer* /*renderer*/)
{
    int     centerX = x - getX();
    int     centerY = y - getY();

    if (_selectedTool == ToolBox::Rectangle)
        paintRectangle(centerX, centerY);
    else if (_selectedTool == ToolBox::Line)
        paintLine(centerX, centerY);
}

void	PaintFrame::onMouseHover(const int x, const int y, \
	SDL_Renderer* /*renderer*/)
{
    int     centerX = x - getX();
    int     centerY = y - getY();

	setHover(true);

    if (_selectedTool == ToolBox::Line && _lineStart != std::pair{ -1, -1 })
        _lineEnd = { centerX, centerY };

    else if (_selectedTool == ToolBox::Rectangle && _rectStart != std::pair{ -1, -1 })
        _rectEnd = { centerX, centerY };
}

void	PaintFrame::onMouseHoverOutside(SDL_Renderer* /*renderer*/)
{
    setHover(false);
}
