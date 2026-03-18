#include "PaintSoftware.hpp"

PaintSoftware::PaintSoftware(const string& name, const int width, const int height, \
    const int frameWidth, const int frameHeight) : \
		Window(name, width, height)
{
	setBackgroundColor(BLACK);
	setWriteColor(WHITE);

	SDL_Renderer*	renderer = getRenderer();

	initFrame(frameWidth, frameHeight);

	initMainButtons(renderer);
	initTools(renderer);
	initBrushOptions(renderer);
}

void	PaintSoftware::initFrame(const int frameWidth, const int frameHeight)
{
	int		frameSpaceWidth = getWidth() - DEF_LEFT_W - DEF_RIGHT_W;
	int		frameSpaceHeight = getHeight() - DEF_UP_H - DEF_DOWN_H;

	int		frameX = DEF_LEFT_W + ((frameSpaceWidth / 2) - (frameWidth / 2));
	int		frameY = DEF_UP_H + ((frameSpaceHeight / 2) - (frameHeight / 2));

	_paintFrame.emplace(frameX, frameY, frameWidth, frameHeight);
}

void	PaintSoftware::initMainButtons(SDL_Renderer* renderer)
{
	_mainBox.emplace(W_LIMIT, H_UP_LIMIT, 150, 130, \
		getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintSoftware::initTools(SDL_Renderer* renderer)
{
	_toolBox.emplace(W_LIMIT, H_UP_LIMIT + (DEF_BUTTON_H * 2) + CENTER_SPACE_H, \
		150, 260, getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintSoftware::initBrushOptions(SDL_Renderer* renderer)
{
	_brushOptions.emplace(W_LIMIT, H_UP_LIMIT + (DEF_BUTTON_H * 6) + (CENTER_SPACE_H * 2), \
		150, 205, getBackgroundColor(), getWriteColor(), renderer);

	if (_brushOptions->getY() + _brushOptions->getHeight() + BORDER \
		< _paintFrame->getHeight() + DEF_UP_H)
	{
		_leftEndLine.emplace(W_LIMIT, (_paintFrame->getY() + _paintFrame->getHeight() - BORDER), \
			BRUSH_PANEL_W, BORDER, getWriteColor());
	}
}
