#include "PaintSoftware.hpp"

void    PaintSoftware::updateMain(void)
{
    int     value = _mainBox->getLastButtonClicked();

    // if (value == SAVE)
    //     ;
    // else if (value == CANCEL)
    //     ;
    // else if (value == BACK)
    //     ;
    // else if (value == FORWARD)
    //     ;

    // ...
}

void    PaintSoftware::updateTool(void)
{
    _selectedTool = _toolBox->getSelectedTool();

    // ...
}

void    PaintSoftware::updateBrush(void)
{
    _brushSize = _brushField->getValue();

    // ...
}

void    PaintSoftware::updateOpacity(void)
{
    _selectedColor.a = _opacitySlider->getValue();

    updateColorText();

    // ...
}

void    PaintSoftware::updateColor(const Color& newColor)
{
    _selectedColor.r = newColor.r;
    _selectedColor.g = newColor.g;
    _selectedColor.b = newColor.b;

    _colorButton->setMainColor(newColor);

    updateColorText();
}

void    PaintSoftware::updateColorText(void)
{
    string	colorText = std::to_string(_selectedColor.r) + ", " + std::to_string(_selectedColor.g) \
		+ ", " + std::to_string(_selectedColor.b) + ", " + std::to_string(_selectedColor.a);

    _colorText->update(colorText, LEFT_PANELS_W, false, getRenderer());
    _colorText->setX((DEF_LEFT_W / 2) - (_colorText->getWidth() / 2));
}

void	PaintSoftware::update(void)
{
    if (_mainBox->getLastButtonClicked() != NONE)
        updateMain();
    else if (_toolBox->getSelectedTool() != _selectedTool)
        updateTool();

    else if (_brushField->getValue() != _brushSize)
        updateBrush();
    else if (_opacitySlider->getValue() != _selectedColor.a)
        updateOpacity();
}
