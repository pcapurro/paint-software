#include "MainBox.hpp"

MainBox::MainBox(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
	_buttons.reserve(4);

	auto	saveButton = std::make_unique<ImageButton>(getX(), getY(), DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/green-check.bmp", backColor, BORDER, writeColor, renderer);

	auto	cancelButton = std::make_unique<ImageButton>(getX() + DEF_BUTTON_W + CENTER_SPACE_W, getY(), \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/red-cross.bmp", \
		backColor, BORDER, writeColor, renderer);

	auto	leftButton = std::make_unique<ImageButton>(getX(), getY() + DEF_BUTTON_H, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/left-arrow.bmp", backColor, BORDER, writeColor, renderer);

	auto	rightButton = std::make_unique<ImageButton>(getX() + DEF_BUTTON_W + CENTER_SPACE_W, getY() + DEF_BUTTON_H, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/right-arrow.bmp", \
		backColor, BORDER, writeColor, renderer);

	_buttons.emplace_back(std::move(saveButton));
	_buttons.emplace_back(std::move(cancelButton));

	_buttons.emplace_back(std::move(leftButton));
	_buttons.emplace_back(std::move(rightButton));

	for (auto& button : _buttons)
		button->setSettings(true, BORDER_SELECT, true, \
		SDL_SYSTEM_CURSOR_HAND, false, true);
}

void    MainBox::render(SDL_Renderer* renderer)
{
    for (auto& button : _buttons)
		button->render(renderer);
}
