#include "BrushOptions.hpp"

BrushOptions::BrushOptions(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
	_background.emplace(x, y, width, height, backColor, \
		true, BORDER, writeColor);

	initBrushLines(writeColor, renderer);

	initOpacity(writeColor);
}

void	BrushOptions::initBrushLines(const Color& writeColor, SDL_Renderer* renderer)
{
	_brushCursors.reserve(4);
	_brushLines.reserve(4);

    int		lineHeights[] = BRUSH_LINES;

	for (int i = 0; i < 4; i++)
	{
		int		lineY = getY() + (BRUSH_LINES_SPACE_H * (i + 1));

		Shape	brushLine(getX() + (getWidth() / 2) - BORDER, lineY, \
			getWidth() / 2 - (BORDER * 2), lineHeights[i], writeColor);

		_brushLines.emplace_back(std::move(brushLine));

		int		spaceWidth = (getX() + (getWidth() / 2) - BORDER) - getX();
		int		cursorX = (getX() + BORDER + (spaceWidth / 2)) - (BRUSH_CURSOR_W / 2);
		int		cursorY = lineY + (lineHeights[i] / 2) - (BRUSH_CURSOR_H / 2);

		if (i == _brushCursor)
		{
			_selectedBrush = std::make_unique<ImageButton>(cursorX, cursorY, BRUSH_CURSOR_W, BRUSH_CURSOR_H, \
				"materials/icons/bmp/white-check.bmp", writeColor, 0, writeColor, renderer);

			_selectedBrush->setSettings(false, NONE, true, \
				SDL_SYSTEM_CURSOR_HAND, true, true);
		}
		else
		{
			Shape	brushCursor(cursorX, cursorY, \
				BRUSH_CURSOR_W, BRUSH_CURSOR_H, INVISIBLE);

			brushCursor.setSettings(false, NONE, true, \
				SDL_SYSTEM_CURSOR_HAND, true, true);

			_brushCursors.emplace_back(std::move(brushCursor));
		}
	}
}

void	BrushOptions::initOpacity(const Color& writeColor)
{
	_opacityCursors.reserve(5);
	
	int		opacityLineStartX = getX() + (BORDER * 5);
	int		opacityLineY = (getY() + getHeight()) - OPACITY_LINE_SPACE_H;

	int		opacityWidth = getWidth() - (BORDER * 10);

	_opacityLine.emplace(opacityLineStartX, opacityLineY, \
		opacityWidth, OPACITY_LINE_H, writeColor);

	for (int i = 0; i < 5; i++)
	{
		int	x = opacityLineStartX + (i * opacityWidth / 4);

		Shape	cursor(x - (OPACITY_CURSOR_W / 2), opacityLineY + (OPACITY_LINE_H / 2) \
			- (OPACITY_CURSOR_H / 2), OPACITY_CURSOR_W, OPACITY_CURSOR_H, INVISIBLE);

		if (i == _opacityCursor)
			cursor.setMainColor(writeColor);

		cursor.setSettings(false, NONE, true, \
			SDL_SYSTEM_CURSOR_HAND, true, true);

		_opacityCursors.emplace_back(std::move(cursor));
	}
}

void	BrushOptions::refreshBrush(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == _brushCursor)
		{
			int		lineHeights[] = BRUSH_LINES;
			int		lineY = getY() + (BRUSH_LINES_SPACE_H * (i + 1));

			int		spaceWidth = (getX() + (getWidth() / 2) - BORDER) - getX();

			int		cursorX = (getX() + BORDER + (spaceWidth / 2)) - (BRUSH_CURSOR_W / 2);
			int		cursorY = lineY + (lineHeights[i] / 2) - (BRUSH_CURSOR_H / 2);

			_brushCursors[_brushCursor].setVisibility(false);

			_selectedBrush->setX(cursorX);
			_selectedBrush->setY(cursorY);
		}
		else
			_brushCursors[_brushCursor].setVisibility(true);
	}
}

void	BrushOptions::refreshOpacity(void)
{
	for (int i = 0; i < 5; i++)
	{
		if (i == _opacityCursor)
			_opacityCursors[_opacityCursor].setMainColor(BLACK);
		else
			_opacityCursors[i].setMainColor(INVISIBLE);
	}
}

void	BrushOptions::refresh(void)
{
	refreshBrush();

	refreshOpacity();
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

	for (auto& cursor : _opacityCursors)
		cursor.render(renderer);
}
