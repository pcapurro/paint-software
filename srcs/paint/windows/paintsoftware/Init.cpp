#include "PaintSoftware.hpp"

PaintSoftware::PaintSoftware(const string& name, const int width, const int height, \
    const int frameWidth, const int frameHeight) : \
		Window(name, width, height)
{
	setBackgroundColor(BLACK);
	setWriteColor(WHITE);

	std::srand(std::time(nullptr));

	_selectedColor = generateRandomColor();

	SDL_Renderer*	renderer = getRenderer();

	initFrame(frameWidth, frameHeight);

	initMainButtons(renderer);
	initTools(renderer);

	initBrushTools(renderer);

	initColors(renderer);

	if (_colorButton->getY() + _colorButton->getHeight() < \
		(_paintFrame->getY() + _paintFrame->getHeight()) - (LINE / 2) - CENTER_SPACE_H)
	{
		_endLine.emplace(W_LIMIT, _paintFrame->getY() + _paintFrame->getHeight() - (LINE / 2), \
			LEFT_PANELS_W, (LINE / 2), getWriteColor());
	}
}

void	PaintSoftware::initFrame(const int frameWidth, const int frameHeight)
{
	int		frameSpaceWidth = getWidth() - DEF_LEFT_W - DEF_RIGHT_W;
	int		frameSpaceHeight = getHeight() - DEF_UP_H - DEF_DOWN_H;

	int		frameX = DEF_LEFT_W + ((frameSpaceWidth / 2) - (frameWidth / 2));
	int		frameY = DEF_UP_H + ((frameSpaceHeight / 2) - (frameHeight / 2));

	Color	backColor = getWriteColor();

	_paintFrame.emplace(frameX, frameY, frameWidth, frameHeight, backColor);
}

void	PaintSoftware::initMainButtons(SDL_Renderer* renderer)
{
	_mainBox.emplace(W_LIMIT, H_UP_LIMIT, LEFT_PANELS_W, DEF_MAIN_H, \
		getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintSoftware::initTools(SDL_Renderer* renderer)
{
	_toolBox.emplace(W_LIMIT, _mainBox->getY() + _mainBox->getHeight() + CENTER_SPACE_H, \
		LEFT_PANELS_W, DEF_TOOLBOX_H, getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintSoftware::initBrushTools(SDL_Renderer* renderer)
{
	string	fontPath = "materials/font/OpenSans.ttf";

	Color	backColor = getBackgroundColor();
	Color	writeColor = getWriteColor();

	_brushSlider.emplace(W_LIMIT, _toolBox->getY() + _toolBox->getHeight() + CENTER_SPACE_H, \
		LEFT_PANELS_W, DEF_SLIDEBOX_H, fontPath, BRUSH_SIZE_MIN, BRUSH_SIZE_MAX, BRUSH_DEF_SIZE, \
		"Brush size: ", 11, true, 2, backColor, writeColor, writeColor, writeColor, renderer);

	_opacitySlider.emplace(W_LIMIT, _brushSlider->getY() + _brushSlider->getHeight() + BORDER, \
		LEFT_PANELS_W, DEF_SLIDEBOX_H, fontPath, OPACITY_MIN, OPACITY_MAX, OPACITY_DEF, \
		"Opacity: ", 11, true, 2, backColor, writeColor, writeColor, writeColor, renderer);
}

void	PaintSoftware::initColors(SDL_Renderer* renderer)
{
	Color	black = BLACK;
	Color	white = WHITE;

	string	fontPath = "materials/font/OpenSans.ttf";
	Color	writeColor = getWriteColor();

	string	colorText = std::to_string(_selectedColor.r) + ", " + std::to_string(_selectedColor.g) \
		+ ", " + std::to_string(_selectedColor.b) + ", " + std::to_string(_selectedColor.a);

	_colorText.emplace(0, _opacitySlider->getY() + _opacitySlider->getHeight() \
		+ CENTER_SPACE_H, colorText, 12, fontPath, getWriteColor(), LEFT_PANELS_W, \
		false, renderer);

	_colorText->setX((DEF_LEFT_W / 2) - (_colorText->getWidth() / 2), renderer);

	_colorButton.emplace(W_LIMIT, _colorText->getY() + _colorText->getHeight() \
		+ (CENTER_SPACE_H / 2), (DEF_BUTTON_W * 2 + CENTER_SPACE_W), DEF_MAIN_COLOR_H, \
		_selectedColor, getWriteColor(), renderer);

	_blackButton.emplace(W_LIMIT, _colorButton->getY() + _colorButton->getHeight() \
		+ (CENTER_SPACE_H / 2), DEF_BUTTON_W, DEF_SIDE_COLOR_H, black, getWriteColor(), renderer);

	_whiteButton.emplace(W_LIMIT + _blackButton->getWidth() + CENTER_SPACE_W, \
		_colorButton->getY() + _colorButton->getHeight() + (CENTER_SPACE_H / 2), \
		DEF_BUTTON_W, DEF_SIDE_COLOR_H, white, getWriteColor(), renderer);
}
