#include "Paint.hpp"

Paint::~Paint(void)
{
	delete _mainWindow;

	if (_normalCursor != nullptr && _normalCursor != NULL)
		SDL_FreeCursor(_normalCursor);
	if (_interactCursor != nullptr && _interactCursor != NULL)
		SDL_FreeCursor(_interactCursor);

	SDL_Quit();
}
