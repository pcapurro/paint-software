#include "ToolBox.hpp"

ToolBox::ToolBox(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
	_buttons.reserve(8);

	int		globalY = H_UP_LIMIT + (DEF_BUTTON_H * 2) + CENTER_SPACE_H;

	auto	brushButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/brush.bmp", backColor, BORDER, writeColor, renderer);
	auto	pencilButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/pencil.bmp", backColor, BORDER, writeColor, renderer);

	globalY += DEF_BUTTON_H;

	auto	bucketButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/bucket.bmp", backColor, BORDER, writeColor, renderer);
	auto	sprayButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/spray.bmp", \
		backColor, BORDER, writeColor, renderer);

	globalY += DEF_BUTTON_H;

	auto	eraserButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/eraser.bmp", backColor, BORDER, writeColor, renderer);
	auto	pickerButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/color-picker.bmp", \
		backColor, BORDER, writeColor, renderer);

	globalY += DEF_BUTTON_H;

	auto	lineButton = std::make_unique<ImageButton>(W_LIMIT, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/line.bmp", backColor, BORDER, writeColor, renderer);
	auto	textButton = std::make_unique<ImageButton>(W_LIMIT + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/text.bmp", \
		backColor, BORDER, writeColor, renderer);

	_buttons.emplace_back(std::move(brushButton));
	_buttons.emplace_back(std::move(pencilButton));

	_buttons.emplace_back(std::move(bucketButton));
	_buttons.emplace_back(std::move(sprayButton));

	_buttons.emplace_back(std::move(eraserButton));
	_buttons.emplace_back(std::move(pickerButton));

	_buttons.emplace_back(std::move(lineButton));
	_buttons.emplace_back(std::move(textButton));
}

void    ToolBox::render(SDL_Renderer* renderer)
{
    for (auto& button : _buttons)
        button->render(renderer);
}
