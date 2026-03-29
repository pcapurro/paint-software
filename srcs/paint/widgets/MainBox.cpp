#include "MainBox.hpp"

MainBox::MainBox(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, SDL_SYSTEM_CURSOR_HAND, false, false})
{
	setMainColor(writeColor);
	setHoverCursor(SDL_SYSTEM_CURSOR_HAND);

	initButtons(renderer);
}

void	MainBox::initButtons(SDL_Renderer* renderer)
{
	_buttons.reserve(4);

	Color	writeColor = getMainColor();
	Color	invisible = Color::Invisible;

	auto	saveButton = std::make_unique<ImageButton>(getX(), getY(), ButtonWidth, ButtonHeight, \
		"materials/icons/bmp/mainbox/green-check.bmp", invisible, Border, writeColor, renderer);

	auto	cancelButton = std::make_unique<ImageButton>(getX() + ButtonWidth + CenterSpaceWidth, getY(), \
		ButtonWidth, ButtonHeight, "materials/icons/bmp/mainbox/red-cross.bmp", \
		invisible, Border, writeColor, renderer);

	auto	leftButton = std::make_unique<ImageButton>(getX(), getY() + ButtonHeight, ButtonWidth, ButtonHeight, \
		"materials/icons/bmp/mainbox/left-arrow.bmp", invisible, Border, writeColor, renderer);

	auto	rightButton = std::make_unique<ImageButton>(getX() + ButtonWidth + CenterSpaceWidth, getY() + ButtonHeight, \
		ButtonWidth, ButtonHeight, "materials/icons/bmp/mainbox/right-arrow.bmp", \
		invisible, Border, writeColor, renderer);

	_buttons.emplace_back(std::move(saveButton));
	_buttons.emplace_back(std::move(cancelButton));

	_buttons.emplace_back(std::move(leftButton));
	_buttons.emplace_back(std::move(rightButton));

	for (auto& button : _buttons)
	{
		button->setSettings(false, State::None, false, \
			State::None, true, true);
	}
}

int		MainBox::getLastButtonClicked(void)
{
	return std::exchange(_lastButtonClicked, State::None);
}

void    MainBox::render(SDL_Renderer* renderer)
{
    for (auto& button : _buttons)
		button->render(renderer);
}

void	MainBox::onMouseDown(const int x, const int y, \
	SDL_Renderer* renderer)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->isAbove(x, y))
		{
			setHover(true);

			_buttons[i]->setHighlight(true);
			_buttons[i]->setFocus(true);
		}
		else if (_buttons[i]->isHover())
			_buttons[i]->setFocus(false);
	}
}

void	MainBox::onMouseUp(const int x, const int y, \
	SDL_Renderer* renderer)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->isAbove(x, y))
		{
			_buttons[i]->setFocus(false);
			_buttons[i]->setSelected(true);

			_lastButtonClicked = i + 1;
		}
		else if (_buttons[i]->isSelected())
			_buttons[i]->setSelected(false);
	}
}

void	MainBox::onMouseHover(const int x, const int y, \
	SDL_Renderer* renderer)
{
	setHover(false);

	for (const auto& button : _buttons)
	{
		if (button->isAbove(x, y))
		{
			setHover(true);

			if (!button->isHighlighted())
				button->setHighlight(true);
		}
		else
		{
			if (button->isHighlighted())
				button->setHighlight(false);

			if (button->isFocused())
				button->setFocus(false);
		}
	}
}

void	MainBox::onMouseHoverOutside(SDL_Renderer* renderer)
{
	setHover(false);

	for (auto& button : _buttons)
	{
		button->setFocus(false);
		button->setHighlight(false);
	}
}
