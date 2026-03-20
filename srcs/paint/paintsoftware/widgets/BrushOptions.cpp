#include "BrushOptions.hpp"

BrushOptions::BrushOptions(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, SDL_SYSTEM_CURSOR_HAND, false, false})
{
	setMainColor(writeColor);
	setHoverCursor(SDL_SYSTEM_CURSOR_HAND);

	_background.emplace(x, y, width, height, backColor, \
		true, BORDER, writeColor);

	initBrushLines(renderer);
	initOpacity();
}

void	BrushOptions::initBrushLines(SDL_Renderer* renderer)
{
	_brushCursors.reserve(4);
	_brushLines.reserve(4);

    int		lineHeights[] = BRUSH_LINES;

	Color	mainColor = getMainColor();
	Color	invisible = INVISIBLE;

	for (int i = 0; i < 4; i++)
	{
		int		lineY = getY() + (BRUSH_LINES_SPACE_H * (i + 1));

		Shape	brushLine(getX() + (getWidth() / 2) - BORDER, lineY, \
			getWidth() / 2 - (BORDER * 2), lineHeights[i], mainColor);

		_brushLines.emplace_back(std::move(brushLine));

		int		spaceWidth = (getX() + (getWidth() / 2) - BORDER) - getX();
		int		cursorX = (getX() + BORDER + (spaceWidth / 2)) - (BRUSH_CURSOR_W / 2);
		int		cursorY = lineY + (lineHeights[i] / 2) - (BRUSH_CURSOR_H / 2);

		if (i == _brushValue)
		{
			_selectedBrush = std::make_unique<ImageButton>(cursorX, cursorY, BRUSH_CURSOR_W, BRUSH_CURSOR_H, \
				"materials/icons/bmp/white-check.bmp", mainColor, 2, mainColor, renderer);

			_selectedBrush->setSettings(false, NONE, true, \
				SDL_SYSTEM_CURSOR_HAND, true, true);
		}

		Shape	brushCursor(cursorX, cursorY, \
			BRUSH_CURSOR_W, BRUSH_CURSOR_H, getMainColor(), true, 4, getMainColor());

		brushCursor.setSettings(false, NONE, true, \
			SDL_SYSTEM_CURSOR_HAND, true, true);

		_brushCursors.emplace_back(std::move(brushCursor));
	}
}

void	BrushOptions::initOpacity(void)
{	
	int		opacityLineStartX = getX() + (BORDER * 5);
	int		opacityLineY = (getY() + getHeight()) - OPACITY_LINE_SPACE_H;

	int		opacityWidth = getWidth() - (BORDER * 10);

	_opacityLine.emplace(opacityLineStartX, opacityLineY, \
		opacityWidth, OPACITY_LINE_H, getMainColor());

	_opacityBox.emplace(opacityLineStartX, opacityLineY - (OPACITY_CURSOR_H), \
		opacityWidth, OPACITY_CURSOR_H * 3, getMainColor());

	_opacityBox->setSettings(false, NONE, true, \
		SDL_SYSTEM_CURSOR_HAND, true, false);

	int		cursorX = (_opacityValue * opacityWidth) / 100;

	_opacityCursor.emplace(opacityLineStartX + (cursorX - (OPACITY_CURSOR_W / 2)), \
		opacityLineY - (OPACITY_CURSOR_H / 2), OPACITY_CURSOR_W, OPACITY_CURSOR_H, getMainColor());
}

void	BrushOptions::refreshBrush(SDL_Renderer* renderer)
{
	int		lineHeights[] = BRUSH_LINES;
	int		lineY = getY() + (BRUSH_LINES_SPACE_H * (_brushValue + 1));

	int		spaceWidth = (getX() + (getWidth() / 2) - BORDER) - getX();

	int		cursorX = (getX() + BORDER + (spaceWidth / 2)) - (BRUSH_CURSOR_W / 2);
	int		cursorY = lineY + (lineHeights[_brushValue] / 2) - (BRUSH_CURSOR_H / 2);

	_selectedBrush->setX(cursorX, renderer);
	_selectedBrush->setY(cursorY, renderer);
}

void	BrushOptions::refreshOpacity(const int x, const int y)
{
	int		opacityLineStartX = getX() + (BORDER * 5);
	int		opacityWidth = getWidth() - (BORDER * 10);

	if (x < opacityLineStartX || x > opacityLineStartX + opacityWidth)
		return;

	int		newOpacity = ((x - opacityLineStartX) * 100) / (opacityWidth);

	_opacityCursor->setX(x);
	_opacityValue = newOpacity;
}

int		BrushOptions::getBrush(void) const noexcept
{
	return _brushValue;
}

int		BrushOptions::getOpacity(void) const noexcept
{
	return _opacityValue;
}

void    BrushOptions::render(SDL_Renderer* renderer)
{
    _background->render(renderer);

    for (auto& line : _brushLines)
        line.render(renderer);

    for (auto& cursor : _brushCursors)
        cursor.render(renderer);

	_selectedBrush->render(renderer);

	_opacityLine->render(renderer);
	_opacityCursor->render(renderer);
}

void	BrushOptions::onMouseDown(const int x, const int y, \
	SDL_Renderer* renderer)
{
	for (auto& cursor : _brushCursors)
	{
		if (cursor.isAbove(x, y))
		{
			setHover(true);

			cursor.setHighlight(true);
			cursor.setFocus(true);
		}
		else
		{
			if (cursor.isHover())
				cursor.setFocus(false);
		}
	}

	if (_opacityBox->isAbove(x, y))
	{
		setClick(true);
		refreshOpacity(x, y);
	}
}

void	BrushOptions::onMouseUp(const int x, const int y, \
	SDL_Renderer* renderer)
{
	for (int i = 0; i < _brushCursors.size(); i++)
	{
		if (_brushCursors[i].isAbove(x, y))
		{
			_brushValue = i;
			refreshBrush(renderer);
		}
	}

	if (_opacityBox->isAbove(x, y))
		setClick(false);
}

void	BrushOptions::onMouseHover(const int x, const int y, \
	SDL_Renderer* renderer)
{
	setHover(false);

	for (auto& cursor : _brushCursors)
	{
		if (cursor.isAbove(x, y))
		{
			setHover(true);

			if (!cursor.isHighlighted())
				cursor.setHighlight(true);
		}
		else
		{
			if (cursor.isHighlighted())
				cursor.setHighlight(false);

			if (cursor.isFocused())
				cursor.setFocus(false);
		}
	}

	if (_opacityBox->isAbove(x, y))
	{
		setHover(true);

		if (isClicked())
			refreshOpacity(x, y);
	}
}

void	BrushOptions::onMouseHoverOutside(SDL_Renderer* renderer)
{
	setHover(false);

	for (auto& cursor : _brushCursors)
	{
		cursor.setFocus(false);
		cursor.setHighlight(false);
	}
}
