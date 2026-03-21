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

	initBrushTools(renderer);
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
	_mainBox.emplace(W_LIMIT, H_UP_LIMIT, LEFT_PANELS_W, 130, \
		getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintSoftware::initTools(SDL_Renderer* renderer)
{
	_toolBox.emplace(W_LIMIT, _mainBox->getY() + _mainBox->getHeight() + CENTER_SPACE_H, \
		LEFT_PANELS_W, 260, getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintSoftware::initBrushTools(SDL_Renderer* renderer)
{
	string	fontPath = "materials/font/OpenSans.ttf";

	Color	backColor = getBackgroundColor();
	Color	writeColor = getWriteColor();

	_brushSlider.emplace(W_LIMIT, _toolBox->getY() + _toolBox->getHeight() + CENTER_SPACE_H, \
		LEFT_PANELS_W, 45, fontPath, 1, 25, "Brush size: ", 11, true, 2, backColor, writeColor, \
		writeColor, writeColor, renderer);

	_opacitySlider.emplace(W_LIMIT, _brushSlider->getY() + _brushSlider->getHeight() + (CENTER_SPACE_H / 2), \
		LEFT_PANELS_W, 45, fontPath, 1, 100, "Opacity: ", 11, true, 2, backColor, writeColor, \
		writeColor, writeColor, renderer);
}
