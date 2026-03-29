#include "ToolBox.hpp"

ToolBox::ToolBox(const int x, const int y, const int width, const int height, \
    const Color& /*backColor*/, const Color& writeColor, SDL_Renderer* renderer) : \
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
	Color	invisible = Color::Invisible;

	auto	brushButton = std::make_unique<ImageButton>(globalX, globalY, ButtonWidth, ButtonHeight, \
		"materials/icons/bmp/toolbox/brush.bmp", invisible, Border, writeColor, renderer);
	auto	pencilButton = std::make_unique<ImageButton>(globalX + ButtonWidth + CenterSpaceWidth, globalY, \
		ButtonWidth, ButtonHeight, "materials/icons/bmp/toolbox/pencil.bmp", invisible, Border, writeColor, renderer);

	globalY += ButtonHeight;

	auto	bucketButton = std::make_unique<ImageButton>(globalX, globalY, ButtonWidth, ButtonHeight, \
		"materials/icons/bmp/toolbox/bucket.bmp", invisible, Border, writeColor, renderer);
	auto	sprayButton = std::make_unique<ImageButton>(globalX + ButtonWidth + CenterSpaceWidth, globalY, \
		ButtonWidth, ButtonHeight, "materials/icons/bmp/toolbox/spray.bmp", \
		invisible, Border, writeColor, renderer);

	globalY += ButtonHeight;

	auto	eraserButton = std::make_unique<ImageButton>(globalX, globalY, ButtonWidth, ButtonHeight, \
		"materials/icons/bmp/toolbox/eraser.bmp", invisible, Border, writeColor, renderer);
	auto	pickerButton = std::make_unique<ImageButton>(globalX + ButtonWidth + CenterSpaceWidth, globalY, \
		ButtonWidth, ButtonHeight, "materials/icons/bmp/toolbox/color-picker.bmp", \
		invisible, Border, writeColor, renderer);

	globalY += ButtonHeight;

	auto	lineButton = std::make_unique<ImageButton>(globalX, globalY, ButtonWidth, ButtonHeight, \
		"materials/icons/bmp/toolbox/line.bmp", invisible, Border, writeColor, renderer);
	auto	rectangleButton = std::make_unique<ImageButton>(globalX + ButtonWidth + CenterSpaceWidth, globalY, \
		ButtonWidth, ButtonHeight, "materials/icons/bmp/toolbox/rectangle.bmp", \
		invisible, Border, writeColor, renderer);

	_buttons.emplace_back(std::move(brushButton));
	_buttons.emplace_back(std::move(pencilButton));

	_buttons.emplace_back(std::move(bucketButton));
	_buttons.emplace_back(std::move(sprayButton));

	_buttons.emplace_back(std::move(eraserButton));
	_buttons.emplace_back(std::move(pickerButton));

	_buttons.emplace_back(std::move(lineButton));
	_buttons.emplace_back(std::move(rectangleButton));

	Color	selectColor = {25, 200, 50, 130};

	for (auto& button : _buttons)
	{
		button->setSettings(true, Render::CenterSelect, \
			false, false, true, true);

		button->setSelectColor(selectColor);
	}

	_buttons[Brush - 1]->setSelected(true);
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
	SDL_Renderer* /*renderer*/)
{
	for (size_t i = 0; i < _buttons.size(); i++)
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

void	ToolBox::onMouseUp(const int x, const int y, \
	SDL_Renderer* /*renderer*/)
{
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->isAbove(x, y))
		{
			_buttons[i]->setFocus(false);
			_buttons[i]->setSelected(true);

			_selectedTool = i + 1;
		}
		else if (_buttons[i]->isSelected())
			_buttons[i]->setSelected(false);
	}
}

void	ToolBox::onMouseHover(const int x, const int y, \
	SDL_Renderer* /*renderer*/)
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

void	ToolBox::onMouseHoverOutside(SDL_Renderer* /*renderer*/)
{
	setHover(false);

	for (auto& button : _buttons)
	{
		button->setFocus(false);
		button->setHighlight(false);
	}
}
