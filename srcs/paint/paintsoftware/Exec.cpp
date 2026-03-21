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
    int     newBrushValue = _brushSlider->getValue();
    int     newOpacityValue = _opacitySlider->getValue();

    if (newBrushValue != _brushSize)
    {
        _brushSize = newBrushValue;

        // ...
    }

    if (newOpacityValue != _selectedColor.a)
        _selectedColor.a = newOpacityValue;
}

void    PaintSoftware::execColor(void)
{
    Color   color = _colorButton->getMainColor();

    if (_selectedColor == color)
        return;

    _colorButton->setMainColor(_selectedColor);

    // ...
}

void	PaintSoftware::exec(void)
{
	execMain();
    execTool();
}
