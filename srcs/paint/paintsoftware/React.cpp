#include "PaintSoftware.hpp"

int		PaintSoftware::reactEvent(SDL_Event* event, const int x, const int y)
{
	int		value = OK;

	if (event->type == SDL_MOUSEMOTION)
		;
    
    if (event->button.button == SDL_BUTTON_LEFT)
    {
        if (event->type == SDL_MOUSEBUTTONDOWN)
            ;
        else if (event->type == SDL_MOUSEBUTTONUP)
            ;
    }

	refreshDisplay();

	return value;
}
