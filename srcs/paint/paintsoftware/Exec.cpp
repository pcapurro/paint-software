#include "PaintSoftware.hpp"

void    PaintSoftware::execMain(void)
{
    int     value = _mainBox->getLastButtonClicked();

    if (value == NONE)
        return;

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

void    PaintSoftware::execTool(void)
{
    int     value = _toolBox->getSelectedTool();

    if (value == _selectedTool)
        return;

    _selectedTool = value;

    // ...
}

void    PaintSoftware::execBrush(void)
{
    int     newBrushValue = _brushField->getValue();
    int     newOpacityValue = _opacitySlider->getValue();

    if (newBrushValue != _brushSize)
    {
        _brushSize = newBrushValue;

        // ...
    }

    if (newOpacityValue != _selectedColor.a)
    {
        _selectedColor.a = newOpacityValue;
        execColor();
    }
}

void    PaintSoftware::execColor(void)
{
    Color   color = _colorButton->getMainColor();

    if (_selectedColor == color)
        return;

    _colorButton->setMainColor(_selectedColor);

    string	colorText = std::to_string(_selectedColor.r) + ", " + std::to_string(_selectedColor.g) \
		+ ", " + std::to_string(_selectedColor.b) + ", " + std::to_string(_selectedColor.a);

    _colorText->update(colorText, LEFT_PANELS_W, false, getRenderer());

    // ...
}

void	PaintSoftware::exec(void)
{
	execMain();
    execTool();
}
