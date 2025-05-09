#include "Paint.hpp"

void	Paint::loadTextures(void)
{
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

void	Paint::initializeSDL(void)
{
	_mainWindow = nullptr;

	_saveWindow = nullptr;
	_cancelWindow = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL failed.");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	_normalCursor = nullptr;
	_interactCursor = nullptr;

	_normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	_interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (_normalCursor == NULL || _interactCursor == NULL)
		throw std::runtime_error("SDL failed.");

	_mainWindow = new ClassicWindow("🎨 paint-software", _width, _height);
}

void	Paint::generateColors(void)
{
	_currentColor.r = 0, _currentColor.g = 0, _currentColor.b = 0;
	_currentColor.a = 255;

	_colorsUp.reserve(20);
	_colorsDown.reserve(20);

	for (int i = 0; i != 20; i++)
	{
		_colorsUp.push_back({getRandomNumber() % 256, \
			getRandomNumber() % 256, getRandomNumber() % 256, 255});
		_colorsDown.push_back({getRandomNumber() % 256, \
			getRandomNumber() % 256, getRandomNumber() % 256, 255});
	}
}

Paint::Paint(void)
{
	_width = 1500;
	_height = 900;
	
	generateColors();

	initializeSDL();
	loadTextures();
}
