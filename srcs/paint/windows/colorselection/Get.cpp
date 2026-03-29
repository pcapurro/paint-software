#include "ColorSelection.hpp"

bool    ColorSelection::error(void) const noexcept
{
    return _error;
}

Color   ColorSelection::getFinalColor(void) const
{
    Color   color;

    color.r = _leftUpField->getValue();
    color.g = _rightUpField->getValue();
    color.b = _leftDownField->getValue();

    color.a = _rightDownField->getValue();

    return color;
}
