#include "ToolBox.hpp"

ToolBox::ToolBox(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, SDL_SYSTEM_CURSOR_HAND, false, false})
{
	setMainColor(writeColor);
	setHoverCursor(SDL_SYSTEM_CURSOR_HAND);

	initButtons(renderer);
}

void	ToolBox::initButtons(SDL_Renderer* renderer)
{
	_buttons.reserve(8);

	int		globalX = getX();
	int		globalY = getY();

	Color	writeColor = getMainColor();
	Color	invisible = INVISIBLE;

	auto	brushButton = std::make_unique<ImageButton>(globalX, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/brush.bmp", invisible, BORDER, writeColor, renderer);
	auto	pencilButton = std::make_unique<ImageButton>(globalX + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/pencil.bmp", invisible, BORDER, writeColor, renderer);

	globalY += DEF_BUTTON_H;

	auto	bucketButton = std::make_unique<ImageButton>(globalX, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/bucket.bmp", invisible, BORDER, writeColor, renderer);
	auto	sprayButton = std::make_unique<ImageButton>(globalX + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/spray.bmp", \
		invisible, BORDER, writeColor, renderer);

	globalY += DEF_BUTTON_H;

	auto	eraserButton = std::make_unique<ImageButton>(globalX, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/eraser.bmp", invisible, BORDER, writeColor, renderer);
	auto	pickerButton = std::make_unique<ImageButton>(globalX + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/color-picker.bmp", \
		invisible, BORDER, writeColor, renderer);

	globalY += DEF_BUTTON_H;

	auto	lineButton = std::make_unique<ImageButton>(globalX, globalY, DEF_BUTTON_W, DEF_BUTTON_H, \
		"materials/icons/bmp/line.bmp", invisible, BORDER, writeColor, renderer);
	auto	textButton = std::make_unique<ImageButton>(globalX + DEF_BUTTON_W + CENTER_SPACE_W, globalY, \
		DEF_BUTTON_W, DEF_BUTTON_H, "materials/icons/bmp/text.bmp", \
		invisible, BORDER, writeColor, renderer);

	_buttons.emplace_back(std::move(brushButton));
	_buttons.emplace_back(std::move(pencilButton));

	_buttons.emplace_back(std::move(bucketButton));
	_buttons.emplace_back(std::move(sprayButton));

	_buttons.emplace_back(std::move(eraserButton));
	_buttons.emplace_back(std::move(pickerButton));

	_buttons.emplace_back(std::move(lineButton));
	_buttons.emplace_back(std::move(textButton));

	for (auto& button : _buttons)
	{
		button->setSettings(true, BORDER_SELECT, \
			false, false, true, true);

		button->setSelectColor(GREEN);
	}
}

int		ToolBox::getSelectedTool(void) const noexcept
{
	return _selectedTool;
}

void    ToolBox::render(SDL_Renderer* renderer)
{
    for (auto& button : _buttons)
        button->render(renderer);
}

void	ToolBox::onMouseDown(const int x, const int y, \
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
		else
		{
			if (_buttons[i]->isHover())
				_buttons[i]->setFocus(false);
		}
	}
}

void	ToolBox::onMouseUp(const int x, const int y, \
	SDL_Renderer* renderer)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->isAbove(x, y))
		{
			_buttons[i]->setSelected(true);
			_selectedTool = i;
		}
	}
}

void	ToolBox::onMouseHover(const int x, const int y, \
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

void	ToolBox::onMouseHoverOutside(SDL_Renderer* renderer)
{
	setHover(false);

	for (auto& button : _buttons)
	{
		button->setFocus(false);
		button->setHighlight(false);
	}
}
