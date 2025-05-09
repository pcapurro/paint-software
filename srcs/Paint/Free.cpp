#include "Paint.hpp"

Paint::~Paint(void)
{
	if (_mainWindow != nullptr)
		delete _mainWindow;

	if (_saveWindow != nullptr)
		delete _saveWindow;
	if (_cancelWindow != nullptr)
		delete _cancelWindow;

	if (_normalCursor != nullptr && _normalCursor != NULL)
		SDL_FreeCursor(_normalCursor);
	if (_interactCursor != nullptr && _interactCursor != NULL)
		SDL_FreeCursor(_interactCursor);

	SDL_Quit();
}
