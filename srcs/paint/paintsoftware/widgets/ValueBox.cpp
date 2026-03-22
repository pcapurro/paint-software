#include "ValueBox.hpp"

ValueBox::ValueBox(const int x, const int y, const int width, const int height, const string& fontPath, \
    const int minValue, const int maxValue, const int defaultValue, const string& title, const string& unit, \
    const int textSize, const bool border, const int borderThickness, const Color& backColor, \
    const Color& borderColor, const Color& textColor, const Color& sliderColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, SDL_SYSTEM_CURSOR_HAND, false, false}), \
        _minValue(minValue), \
        _maxValue(maxValue)
{
    _value = defaultValue;

    _background.emplace(x, y, width, height, \
        backColor, border, borderThickness, borderColor);

    initTitle(title, textSize, fontPath, \
        textColor, renderer);

    initUnit(unit, textSize, fontPath, \
        textColor, renderer);

    initField(fontPath, backColor, \
        textColor, borderColor);

    setHoverCursor(SDL_SYSTEM_CURSOR_HAND);
}

void    ValueBox::initTitle(const string& title, const int textSize, const string& fontPath, \
    const Color& textColor, SDL_Renderer* renderer)
{
    int     x = getX();
    int     y = getY();

    int     borderThickness = _background->getBorderThickness();

    int     titleX = x + borderThickness + (BORDER * 4);
    int     titleY = y + borderThickness + BORDER;

    _title.emplace(titleX, titleY, title, textSize, fontPath, \
        textColor, getWidth(), false, renderer);
}

void    ValueBox::initUnit(const string& unit, const int textSize, const string& fontPath, \
    const Color& textColor, SDL_Renderer* renderer)
{
    _unit.emplace(0, 0, unit, textSize, fontPath, textColor, \
        getWidth(), false, renderer);

    int     borderThickness = _background->getBorderThickness();

    int     fieldY = _title->getY() + _title->getHeight();

    int     unitX = getX() + getWidth() - \
        (borderThickness + (BORDER * 4)) - _unit->getWidth();
    int     unitY = fieldY + (DEF_BRUSH_FIELD_H / 2) - \
        (_unit->getHeight() / 2);

    _unit->setX(unitX, renderer);
    _unit->setY(unitY, renderer);
}

void    ValueBox::initField(const string& fontPath, const Color& backColor, \
    const Color& textColor, const Color& borderColor)
{
    int     x = getX();
    int     y = getY();

    int     borderThickness = _background->getBorderThickness();

    int     fieldX = x + borderThickness + (BORDER * 4);
    int     fieldY = _title->getY() + _title->getHeight();

    int     fieldWidth = getWidth() - (BORDER * 8) - \
        (borderThickness * 2) - _unit->getWidth() - (BORDER * 2);

    _field.emplace(fieldX, fieldY, fieldWidth, DEF_BRUSH_FIELD_H, backColor, \
        borderColor, fontPath, textColor, std::to_string(_maxValue).size(), _minValue, _maxValue);
}

void	ValueBox::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _background->setWidth(properties.width);
    _background->setHeight(properties.height);
}

void	ValueBox::onPositionChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _background->setX(properties.x);
    _background->setY(properties.y);

    if (_title)
    {
        int     titleX = properties.x + _background->getBorderThickness() + (BORDER * 4);
        int     titleY = properties.y + _background->getBorderThickness() + BORDER;

        _title->setX(titleX, renderer);
        _title->setY(titleY, renderer);
    }

    // int     valueX = _title ? _title->getX() + _title->getWidth() + BORDER \
    //     : properties.x + _background->getBorderThickness() + (BORDER * 4);
    // int     valueY = properties.y + _background->getBorderThickness() + BORDER;

    // _valueText->setX(valueX, renderer);
    // _valueText->setY(valueY, renderer);

    // int     sliderX = properties.x + _background->getBorderThickness() + (BORDER * 4);
    // int     sliderY = (properties.y + properties.height) - \
    //     _background->getBorderThickness() - (DEF_SLIDER_H * 2) - (BORDER * 3);

    // _slider->setX(sliderX);
    // _slider->setY(sliderY);

    // int     cursorX = (_value * _slider->getWidth()) / _maxValue;
    // int     cursorY = (sliderY + (DEF_SLIDER_H / 2)) - (SLIDER_CURSOR_H / 2);

    // _cursor->setX(cursorX);
    // _cursor->setY(cursorY);
}

void	ValueBox::onStyleChanged(void)
{
    Shape*      back = &_background.value();

    back->setMainColor(getMainColor());
    back->setSelectColor(getSelectColor());
}

void	ValueBox::onSettingsChanged(void)
{
    Shape*      back = &_background.value();

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

void	ValueBox::onStateChanged(void)
{
    Shape*      back = &_background.value();

    back->setHover(isHover());
    back->setSelected(isSelected());

    back->setHighlight(isHighlighted());
    back->setFocus(isFocused());
}

void	ValueBox::onMouseDown(const int x, const int y, \
	SDL_Renderer* renderer)
{
	// if (_sliderBox->isAbove(x, y))
	// {
		// setClick(true);
		// refreshValue(x, y, renderer);
	// }
}

void	ValueBox::onMouseUp(const int x, const int y, \
	SDL_Renderer* renderer)
{
	// if (_sliderBox->isAbove(x, y))
		// setClick(false);
}

void	ValueBox::onMouseHover(const int x, const int y, \
	SDL_Renderer* renderer)
{
	setHover(false);

	// if (_sliderBox->isAbove(x, y))
	// {
	// 	setHover(true);

	// 	if (isClicked())
	// 		refreshValue(x, y, renderer);
	// }
}

void	ValueBox::onMouseHoverOutside(SDL_Renderer* renderer)
{
	setHover(false);

	// if (isClicked())
	// {
	// 	refreshValue(_sliderBox->getX() \
	// 		+ _sliderBox->getWidth(), _sliderBox->getY(), renderer);

	// 	setClick(false);
	// }
}

void    ValueBox::render(SDL_Renderer* renderer)
{
    _background->render(renderer);

    _title->render(renderer);
    _field->render(renderer);
    _unit->render(renderer);
}

int     ValueBox::getValue(void) const noexcept
{
    return _value;
}
