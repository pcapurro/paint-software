#include "Paint.hpp"

Paint::Paint(void)
{
	_mainWindow = nullptr;

	_width = 1280;
	_height = 720;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL failed.");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	_normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	_interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (_normalCursor == NULL || _interactCursor == NULL)
		throw std::runtime_error("SDL failed.");

	_mainWindow = new ClassicWindow("paint-software", _width, _height);
}
