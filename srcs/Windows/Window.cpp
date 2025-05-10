#include "Window.hpp"

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

	_normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	_interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (_normalCursor == NULL || _interactCursor == NULL)
		throw std::runtime_error("SDL failed.");
}

Window::~Window(void)
{
	if (_normalCursor != nullptr && _normalCursor != NULL)
		SDL_FreeCursor(_normalCursor);
	if (_interactCursor != nullptr && _interactCursor != NULL)
		SDL_FreeCursor(_interactCursor);

	if (_mainRenderer != nullptr && _mainRenderer != NULL)
		SDL_DestroyRenderer(_mainRenderer);
	if (_mainWindow != nullptr && _mainWindow != NULL)
		SDL_DestroyWindow(_mainWindow);
}

void	Window::render(void)
{
	SDL_RenderPresent(_mainRenderer);
}

void	Window::clear(void)
{
	SDL_RenderClear(_mainRenderer);
}

SDL_Renderer*	Window::getRenderer(void) const
{
	return (_mainRenderer);
}

int	Window::getWidth(void) const
{
	return (_width);
}

int	Window::getHeight(void) const
{
	return (_height);
}

SDL_Cursor*		Window::getCursor(const int value) const
{
	if (value == 0)
		return (_normalCursor);
	if (value == 1)
		return (_interactCursor);

	return (nullptr);
}
