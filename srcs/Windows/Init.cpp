#include "Windows.hpp"

Window::Window(const std::string name, const int width, const int height)
{
	_width = width;
	_height = height;

	_name = name;

	_mainWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
		_width, _height, 0);
	if (_mainWindow == NULL)
		throw std::runtime_error("SDL failed.");

	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
		SDL_RENDERER_ACCELERATED);
	if (_mainRenderer == NULL)
		throw std::runtime_error("SDL failed.");

	SDL_RenderClear(_mainRenderer);
}
