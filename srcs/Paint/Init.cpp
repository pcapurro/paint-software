#include "Paint.hpp"

Paint::Paint(void)
{
	_mainWindow = nullptr;

	_width = 1500;
	_height = 900;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL failed.");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	_normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	_interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (_normalCursor == NULL || _interactCursor == NULL)
		throw std::runtime_error("SDL failed.");

	_mainWindow = new ClassicWindow("🎨 paint-software", _width, _height);

	int value = 0;

	value += _textures.brush.load("materials/brush.bmp", _mainWindow->getRenderer());
	value += _textures.pencil.load("materials/pencil.bmp", _mainWindow->getRenderer());

	value += _textures.spray.load("materials/spray.bmp", _mainWindow->getRenderer());
	value += _textures.bucket.load("materials/bucket.bmp", _mainWindow->getRenderer());

	value += _textures.picker.load("materials/picker.bmp", _mainWindow->getRenderer());
	value += _textures.eraser.load("materials/eraser.bmp", _mainWindow->getRenderer());

	value += _textures.check.load("materials/check.bmp", _mainWindow->getRenderer());
	value += _textures.cancel.load("materials/cancel.bmp", _mainWindow->getRenderer());

	value += _textures.random.load("materials/random.bmp", _mainWindow->getRenderer());
	value += _textures.select.load("materials/select.bmp", _mainWindow->getRenderer());

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}
