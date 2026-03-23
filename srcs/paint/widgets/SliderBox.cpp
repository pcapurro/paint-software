#include "SliderBox.hpp"

SliderBox::SliderBox(const int x, const int y, const int width, const int height, const string& fontPath, \
    const int minValue, const int maxValue, const int defaultValue, const string& title, const int textSize, \
    const bool border, const int borderThickness, const Color& backColor, const Color& borderColor, \
    const Color& textColor, const Color& sliderColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height}, {}, {false, false, true, SDL_SYSTEM_CURSOR_HAND, false, false}), \
        _minValue(minValue), \
        _maxValue(maxValue)
{
    _value = defaultValue;

    _background.emplace(x, y, width, height, \
        backColor, border, borderThickness, borderColor);

    initTexts(title, textSize, fontPath, textColor, renderer);

    initSlider(sliderColor);

    setHoverCursor(SDL_SYSTEM_CURSOR_HAND);
}

void    SliderBox::initTexts(const string& title, const int textSize, const string& fontPath, \
    const Color& textColor, SDL_Renderer* renderer)
{
    int     x = getX();
    int     y = getY();

    int     width = getWidth();
    int     height = getHeight();

    int     borderThickness = _background->getBorderThickness();

    if (title.size() > 0)
    {
        int     titleX = x + borderThickness + (BORDER * 4);
        int     titleY = y + borderThickness + BORDER;

        _title.emplace(titleX, titleY, title, textSize, fontPath, \
            textColor, width, false, renderer);
    }

    int     valueX = _title ? _title->getX() + _title->getWidth() + BORDER \
        : x + borderThickness + (BORDER * 4);
    int     valueY = y + borderThickness + BORDER;

    _valueText.emplace(valueX, valueY, std::to_string(_value), \
        textSize, fontPath, textColor, width, false, renderer);
}

void    SliderBox::initSlider(const Color& sliderColor)
{
    int     x = getX();
    int     y = getY();

    int     width = getWidth();
    int     height = getHeight();

    int     borderThickness = _background->getBorderThickness();

    int     sliderX = x + borderThickness + (BORDER * 4);
    int     sliderY = (y + height) - borderThickness - (DEF_SLIDER_H * 2) - (BORDER * 3);

    int     sliderWidth = width - (BORDER * 8) - (borderThickness * 2);

    _slider.emplace(sliderX, sliderY, sliderWidth, \
        DEF_SLIDER_H, sliderColor);

    _slider->setSettings(false, NONE, false, \
        NONE, true, true);

    int     cursorY = (sliderY + (DEF_SLIDER_H / 2)) - (SLIDER_CURSOR_H / 2);

    _cursor.emplace(getX(), cursorY, SLIDER_CURSOR_W, \
        SLIDER_CURSOR_H, sliderColor);

    _cursor->setSettings(false, NONE, false, \
        NONE, true, true);

    refreshCursor();

    Color   invisible = INVISIBLE;

    _sliderBox.emplace(x + borderThickness, _valueText->getY() + \
        _valueText->getHeight(), width - (borderThickness * 2), height - \
        _valueText->getHeight() - ((borderThickness * 2) + BORDER), invisible);
}

void	SliderBox::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _background->setWidth(properties.width);
    _background->setHeight(properties.height);
}

void	SliderBox::onPositionChanged(SDL_Renderer* renderer)
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

    int     valueX = _title ? _title->getX() + _title->getWidth() + BORDER \
        : properties.x + _background->getBorderThickness() + (BORDER * 4);
    int     valueY = properties.y + _background->getBorderThickness() + BORDER;

    _valueText->setX(valueX, renderer);
    _valueText->setY(valueY, renderer);

    int     sliderX = properties.x + _background->getBorderThickness() + (BORDER * 4);
    int     sliderY = (properties.y + properties.height) - \
        _background->getBorderThickness() - (DEF_SLIDER_H * 2) - (BORDER * 3);

    _slider->setX(sliderX);
    _slider->setY(sliderY);

    int     cursorX = (_value * _slider->getWidth()) / _maxValue;
    int     cursorY = (sliderY + (DEF_SLIDER_H / 2)) - (SLIDER_CURSOR_H / 2);

    _cursor->setX(cursorX);
    _cursor->setY(cursorY);
}

void	SliderBox::onStyleChanged(void)
{
    _background->setMainColor(getMainColor());
    _background->setSelectColor(getSelectColor());
}

void	SliderBox::onMouseDown(const int x, const int y, \
	SDL_Renderer* renderer)
{
	if (_sliderBox->isAbove(x, y))
	{
		setClick(true);
		refreshValue(x, y, renderer);

        _slider->setHighlight(false);
        _cursor->setHighlight(false);
	}
}

void	SliderBox::onMouseUp(const int x, const int y, \
	SDL_Renderer* renderer)
{
	if (_sliderBox->isAbove(x, y))
		setClick(false);
}

void	SliderBox::onMouseHover(const int x, const int y, \
	SDL_Renderer* renderer)
{
	setHover(false);

	if (_sliderBox->isAbove(x, y))
	{
		setHover(true);

		if (isClicked())
			refreshValue(x, y, renderer);
        else
        {
            if (!_slider->isHighlighted())
                _slider->setHighlight(true);
            if (!_cursor->isHighlighted())
                _cursor->setHighlight(true);
        }
	}
}

void	SliderBox::onMouseHoverOutside(SDL_Renderer* renderer)
{
	setHover(false);

	if (isClicked())
		setClick(false);

    if (_slider->isHighlighted())
        _slider->setHighlight(false);

    if (_cursor->isHighlighted())
        _cursor->setHighlight(false);
}

void    SliderBox::render(SDL_Renderer* renderer)
{
    _background->render(renderer);

    _title->render(renderer);
    _valueText->render(renderer);

    _slider->render(renderer);
    _cursor->render(renderer);
}

int     SliderBox::getValue(void) const noexcept
{
    return _value;
}

void    SliderBox::update(const int value, SDL_Renderer* renderer)
{
    if (_value == value)
        return;

    _value = value;

    _valueText->update(std::to_string(_value), \
        getWidth(), false, renderer);

    refreshCursor();
}

void    SliderBox::refreshValue(const int x, const int y, SDL_Renderer* renderer)
{
	int		lineStartX = _slider->getX();
    int     lineWidth = _slider->getWidth();

	if (x < lineStartX)
		_value = _minValue;
	else if (x > lineStartX + lineWidth)
		_value = _maxValue;
	else
	{
		_cursor->setX(x);
		_value = ((x - lineStartX) * _maxValue) / lineWidth;
    }

    string  valueText = std::to_string(_value);

    if (valueText != _valueText->getTextStr())
    {
        _valueText->update(std::to_string(_value), \
            getWidth(), false, renderer);
    }
}

void    SliderBox::refreshCursor(void)
{
    int		lineStartX = _slider->getX();
    int     cursorX = (_value * _slider->getWidth()) / _maxValue;

    _cursor->setX(lineStartX + cursorX);
}
