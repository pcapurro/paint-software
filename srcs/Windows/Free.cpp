#include "Windows.hpp"

Window::~Window(void)
{
	if (_mainRenderer != nullptr && _mainRenderer != NULL)
		SDL_DestroyRenderer(_mainRenderer);
	if (_mainWindow != nullptr && _mainWindow != NULL)
		SDL_DestroyWindow(_mainWindow);
}