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

    // ...
}

void    PaintView::updateBrush(void)
{
    _brushSize = _brushSlider->getValue();

    // ...
}

void    PaintView::updateOpacityFromSlider(void)
{
    _selectedColor.a = _opacitySlider->getValue();

    updateColorText();

    // ...
}

void    PaintView::updateOpacityFromValue(const uint8_t opacity)
{
    _selectedColor.a = opacity;
    _opacitySlider->update(opacity, getRenderer());

    updateColorText();
}

void    PaintView::updateColor(const Color& newColor)
{
    _selectedColor.r = newColor.r;
    _selectedColor.g = newColor.g;
    _selectedColor.b = newColor.b;

    _colorButton->setMainColor(newColor);

    updateColorText();
}

void    PaintView::updateColorText(void)
{
    string	colorText = std::to_string(_selectedColor.r) + ", " + std::to_string(_selectedColor.g) \
		+ ", " + std::to_string(_selectedColor.b) + ", " + std::to_string(_selectedColor.a);

    _colorText->update(colorText, LeftPanelsWidth, false, getRenderer());
    _colorText->setX((LeftWidth / 2) - (_colorText->getWidth() / 2));
}

void	PaintView::update(void)
{
    if (_mainBox->getLastButtonClicked() != State::None)
        updateMain();
    else if (_toolBox->getSelectedTool() != _selectedTool)
        updateTool();

    else if (_brushSlider->getValue() != _brushSize)
        updateBrush();
    else if (_opacitySlider->getValue() != _selectedColor.a)
        updateOpacityFromSlider();
}
