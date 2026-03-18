#include "PaintSoftware.hpp"

PaintSoftware::PaintSoftware(const string& name, const int width, const int height, \
    const int frameWidth, const int frameHeight) : \
		Window(name, width, height)
{
	setBackgroundColor(BLACK);
	setWriteColor(WHITE);

	initFrame(frameWidth, frameHeight);

	SDL_Renderer*	renderer = getRenderer();

	initMainButtons(renderer);
	initTools(renderer);

	initBrushOptions(renderer);
	initOpacityOption(renderer);

	initColorsOptions(renderer);
	initRandomColors(renderer);
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
	_mainButtons.reserve(4);

	auto	saveButton = std::make_unique<ImageButton>(W_LIMIT, H_UP_LIMIT, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/green-check.bmp", getBackgroundColor(), 3, getWriteColor(), renderer);
	auto	cancelButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, H_UP_LIMIT, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/red-cross.bmp", \
		getBackgroundColor(), 3, getWriteColor(), renderer);

	auto	leftButton = std::make_unique<ImageButton>(W_LIMIT, H_UP_LIMIT + DEF_BUTTON_H, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/left-arrow.bmp", getBackgroundColor(), 3, getWriteColor(), renderer);
	auto	rightButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, H_UP_LIMIT + DEF_BUTTON_H, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/right-arrow.bmp", \
		getBackgroundColor(), 3, getWriteColor(), renderer);

	_mainButtons.emplace_back(std::move(saveButton));
	_mainButtons.emplace_back(std::move(cancelButton));

	_mainButtons.emplace_back(std::move(leftButton));
	_mainButtons.emplace_back(std::move(rightButton));

	for (auto& button : _mainButtons)
		button->setSettings(true, BORDER_SELECT, true, \
		SDL_SYSTEM_CURSOR_HAND, false, true);
}

void	PaintSoftware::initTools(SDL_Renderer* renderer)
{
	_tools.reserve(8);

	int		globalY = H_UP_LIMIT + (DEF_BUTTON_H * 2) + CENTER_SPACE_H;

	auto	brushButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/brush.bmp", getBackgroundColor(), 3, getWriteColor(), renderer);
	auto	pencilButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/pencil.bmp", getBackgroundColor(), 3, getWriteColor(), renderer);

	globalY += DEF_BUTTON_H;

	auto	bucketButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/bucket.bmp", getBackgroundColor(), 3, getWriteColor(), renderer);
	auto	sprayButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/spray.bmp", \
		getBackgroundColor(), 3, getWriteColor(), renderer);

	globalY += DEF_BUTTON_H;

	auto	eraserButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/eraser.bmp", getBackgroundColor(), 3, getWriteColor(), renderer);
	auto	pickerButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/color-picker.bmp", \
		getBackgroundColor(), 3, getWriteColor(), renderer);

	globalY += DEF_BUTTON_H;

	auto	lineButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/line.bmp", getBackgroundColor(), 3, getWriteColor(), renderer);
	auto	textButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/text.bmp", \
		getBackgroundColor(), 3, getWriteColor(), renderer);

	_tools.emplace_back(std::move(brushButton));
	_tools.emplace_back(std::move(pencilButton));

	_tools.emplace_back(std::move(bucketButton));
	_tools.emplace_back(std::move(sprayButton));

	_tools.emplace_back(std::move(eraserButton));
	_tools.emplace_back(std::move(pickerButton));

	_tools.emplace_back(std::move(lineButton));
	_tools.emplace_back(std::move(textButton));

	// ...
}

void	PaintSoftware::initBrushOptions(SDL_Renderer* renderer)
{
	int		globalY = H_UP_LIMIT + (DEF_BUTTON_H * 6) + (CENTER_SPACE_H * 2);
	Shape	optionsFrame(W_LIMIT, globalY, 150, 205, getBackgroundColor(), true, 3, getWriteColor());

	_brushCursors.reserve(4);
	_opacityCursors.reserve(4);

	_decoyShapes.emplace_back(std::move(optionsFrame));

	// ...
}

void	PaintSoftware::initOpacityOption(SDL_Renderer* renderer)
{
	_opacityCursors.reserve(5);

	// ...
}

void	PaintSoftware::initColorsOptions(SDL_Renderer* renderer)
{
	_colorsOptions.reserve(3);

	// ...
}

void	PaintSoftware::initRandomColors(SDL_Renderer* renderer)
{
	// _randomColors.reserve(42);
	// ...
}
