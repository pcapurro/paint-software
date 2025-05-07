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

	value += _textures.brush.load("materials/ui/brush.bmp", _mainWindow->getRenderer());
	value += _textures.pencil.load("materials/ui/pencil.bmp", _mainWindow->getRenderer());

	value += _textures.spray.load("materials/ui/spray.bmp", _mainWindow->getRenderer());
	value += _textures.bucket.load("materials/ui/bucket.bmp", _mainWindow->getRenderer());

	value += _textures.picker.load("materials/ui/picker.bmp", _mainWindow->getRenderer());
	value += _textures.eraser.load("materials/ui/eraser.bmp", _mainWindow->getRenderer());

	value += _textures.checkB.load("materials/ui/check-b.bmp", _mainWindow->getRenderer());
	value += _textures.cancelB.load("materials/ui/cancel-b.bmp", _mainWindow->getRenderer());

	value += _textures.checkB.load("materials/ui/check-b.bmp", _mainWindow->getRenderer());
	value += _textures.checkG.load("materials/ui/check-g.bmp", _mainWindow->getRenderer());

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}
