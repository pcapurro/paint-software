#include "ColorButton.hpp"

ColorButton::ColorButton(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, SDL_SYSTEM_CURSOR_HAND, false, false})
{
    _back.emplace(x, y, width, height, \
        backColor, true, BORDER, writeColor);

    _back->setSettings(false, NONE, false, \
        NONE, true, true);
}

void	ColorButton::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _back->setWidth(properties.width);
    _back->setHeight(properties.height);
}

void	ColorButton::onPositionChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _back->setX(properties.x);
    _back->setY(properties.y);
}

void	ColorButton::onStyleChanged(void)
{
    Shape*      back = &_back.value();

    back->setMainColor(getMainColor());
    back->setSelectColor(getSelectColor());
}

void	ColorButton::onSettingsChanged(void)
{
    Shape*      back = &_back.value();

    if (isHoverPossible())
    {
        back->enableHover();
        back->setHoverCursor(getHoverCursor());
    }
    else
        back->disableHover();

    if (isSelectPossible())
    {
        back->enableSelect();
        back->setSelectColor(getSelectColor());
    }

    if (isHighlightPossible())
        back->enableHighlight();
    else
        back->disableHighlight();

    if (isFocusPossible())
        back->enableFocus();
    else
        back->disableFocus();
}

void	ColorButton::onStateChanged(void)
{
    Shape*      back = &_back.value();

    back->setHover(isHover());
    back->setSelected(isSelected());

    back->setHighlight(isHighlighted());
    back->setFocus(isFocused());
}

void    ColorButton::render(SDL_Renderer* renderer)
{
    _back->render(renderer);
}

void	ColorButton::onMouseUp(const int x, const int y, \
	SDL_Renderer* renderer)
{
    // ...
}

void	ColorButton::onMouseHover(const int x, const int y, \
	SDL_Renderer* renderer)
{
	setHover(true);

    if (!_back->isHighlighted())
        _back->setHighlight(true);
}

void	ColorButton::onMouseHoverOutside(SDL_Renderer* renderer)
{
	setHover(false);

    if (_back->isHighlighted())
        _back->setHighlight(false);
}
