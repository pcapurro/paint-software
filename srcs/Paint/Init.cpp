#include "Paint.hpp"

Paint::Paint(void)
{
	_mainWindow = nullptr;

	_width = 1280 + 50;
	_height = 720 + 200;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL failed.");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	_normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	_interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (_normalCursor == NULL || _interactCursor == NULL)
		throw std::runtime_error("SDL failed.");

	_mainWindow = new ClassicWindow("🎨 paint-software", _width, _height);

	int value = 0;

	value += _textures.brush.load("materials/icons/brush.bmp", _mainWindow->getRenderer());
	value += _textures.pencil.load("materials/icons/pencil.bmp", _mainWindow->getRenderer());

	value += _textures.eraser.load("materials/icons/eraser.bmp", _mainWindow->getRenderer());
	value += _textures.bucket.load("materials/icons/bucket.bmp", _mainWindow->getRenderer());
	value += _textures.color.load("materials/icons/color-picker.bmp", _mainWindow->getRenderer());

	value += _textures.paint.load("materials/icons/paint.bmp", _mainWindow->getRenderer());
	value += _textures.save.load("materials/icons/save.bmp", _mainWindow->getRenderer());
	value += _textures.settings.load("materials/icons/settings.bmp", _mainWindow->getRenderer());

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}
