#include "PaintView.hpp"

void    PaintView::updateMain(void)
{
    int     value = _mainBox->getLastButtonClicked();

    (void) value;

    // if (value == Save)
    //     ;
    // else if (value == Cancel)
    //     ;
    // else if (value == Back)
    //     ;
    // else if (value == Forward)
    //     ;

    // ...
}

void    PaintView::updateTool(void)
{
    _selectedTool = _toolBox->getSelectedTool();

    _paintFrame->setSelectedTool(_selectedTool);
    updateCursorImage();
}

void    PaintView::updateBrush(void)
{
    _brushSize = _brushSlider->getValue();

    _paintFrame->setBrushSize(_brushSize);

    updateBrushScope();
    updateBrushScopePosition();

    updateCursorPosition();
}

void    PaintView::updateOpacityFromSlider(void)
{
    _selectedColor.a = _opacitySlider->getValue();

    _paintFrame->setSelectedColor(_selectedColor);
    updateColorText();
}

void    PaintView::updateOpacityFromValue(const uint8_t opacity)
{
    _selectedColor.a = opacity;
    _paintFrame->setSelectedColor(_selectedColor);

    _opacitySlider->update(opacity, getRenderer());
}

void    PaintView::updateColor(const Color& newColor)
{
    _selectedColor.r = newColor.r;
    _selectedColor.g = newColor.g;
    _selectedColor.b = newColor.b;

    _colorButton->setMainColor(newColor);
    _paintFrame->setSelectedColor(newColor);
}

void    PaintView::updateColorText(void)
{
    string	colorText = std::to_string(_selectedColor.r) + ", " + std::to_string(_selectedColor.g) \
		+ ", " + std::to_string(_selectedColor.b) + ", " + std::to_string(_selectedColor.a);

    _colorText->update(colorText, LeftPanelsWidth, false, getRenderer());
    _colorText->setX((LeftWidth / 2) - (_colorText->getWidth() / 2));
}

void    PaintView::updateCursorImage(void)
{
    bool    visibility = _customCursor->isVisible();

    int     prevX = _customCursor->getX();
    int     prevY = _customCursor->getY();

    _customCursor.reset();

    if (_selectedTool == ToolBox::Line)
        return;

    _customCursor.emplace(prevX, prevY, DefaultCursorWidth, DefaultCursorHeight, \
        ToolBox::getToolPath(_selectedTool).c_str(), _selectedColor, getRenderer());

    if (_selectedTool == ToolBox::Spray || _selectedTool == ToolBox::Bucket)
        _customCursor->setHorizontalFlip(true);

    _customCursor->setVisibility(visibility);
}

void    PaintView::updateBrushScope(void)
{
    if (_brushScope->getWidth() != _brushSize)
        _brushScope->setWidth(_brushSize);

    if (_brushScope->getHeight() != _brushSize)
        _brushScope->setHeight(_brushSize);

    if (_brushScope->getBorderColor() != _selectedColor)
        _brushScope->setBorderColor(_selectedColor);
}

void    PaintView::updateBrushScopePosition(void)
{
    _brushScope->setX(getCursorX() - (_brushScope->getWidth() / 2));
    _brushScope->setY(getCursorY() - (_brushScope->getHeight() / 2));
}

void    PaintView::updateCursorPosition(void)
{
    _customCursor->setX(_brushScope->getX() + _brushScope->getWidth());

    if (_selectedTool != ToolBox::Spray)
        _customCursor->setY(_brushScope->getY() - DefaultCursorHeight);
    else
        _customCursor->setY(_brushScope->getY() - DefaultCursorHeight / 3);
}

void    PaintView::updateMouse(void)
{
    if (_paintFrame->isAbove(getCursorX(), getCursorY()))
    {
        updateBrushScopePosition();
        updateCursorPosition();

        _customCursor->setVisibility(true);

        if (_selectedTool == ToolBox::Picker || _selectedTool == ToolBox::Line \
            || _selectedTool == ToolBox::Rectangle || _selectedTool == ToolBox::Bucket)
        {
            _brushScope->setVisibility(false);
            SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
        }
        else
        {
            _brushScope->setVisibility(true);
            SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
        }
    }
    else
    {
        _customCursor->setVisibility(false);
        _brushScope->setVisibility(false);
    }
}

void	PaintView::update(void)
{
    if (_mainBox->getLastButtonClicked() != State::None)
        updateMain();

    if (_toolBox->getSelectedTool() != _selectedTool)
        updateTool();

    if (_brushSlider->getValue() != _brushSize)
        updateBrush();

    if (_opacitySlider->getValue() != _selectedColor.a)
        updateOpacityFromSlider();
}
