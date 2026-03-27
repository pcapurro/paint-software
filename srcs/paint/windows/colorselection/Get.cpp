#include "ColorSelection.hpp"

vector<uint8_t>  ColorSelection::getFinalValues(void)
{
    _finalValues.clear();

    uint8_t leftUpValue = _leftUpField->getValue();
    uint8_t rightUpValue = _rightUpField->getValue();

    uint8_t leftDownValue = _leftDownField->getValue();
    uint8_t rightDownValue = _rightDownField->getValue();

    _finalValues.push_back(leftUpValue);
    _finalValues.push_back(rightUpValue);

    _finalValues.push_back(leftDownValue);
    _finalValues.push_back(rightDownValue);

    return _finalValues;
}
