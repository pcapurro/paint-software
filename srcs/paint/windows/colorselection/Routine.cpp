#include "ColorSelection.hpp"

int     ColorSelection::routine(void)
{
    int     value = OK;

	render();
	refreshDisplay();

    while (true)
    {
        value = waitForEvent();

        if (value == OK \
            || (value == RETURN && _error))
            continue;

        _finalValues = { (uint8_t) _leftUpField->getValue(), (uint8_t) _rightUpField->getValue(), \
            (uint8_t) _leftDownField->getValue(), (uint8_t) _rightDownField->getValue() };

        return value;
    }

    return OK;
}
