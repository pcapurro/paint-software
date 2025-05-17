#include "Paint.hpp"

Paint::Paint(void)
{
	initializeSDL();

	_mainWindow = new Software("🎨 paint-software / Edit an image", 1500, 900);
	_otherWindow = new Ok("🎨 paint-software / Welcome");

	_mainWindow->clear();
	_mainWindow->draw();
	_mainWindow->blur();
	_mainWindow->render();
}

Paint::~Paint(void)
{
	if (_mainWindow != nullptr)
		delete _mainWindow;

	if (_otherWindow != nullptr)
		delete _otherWindow;

	TTF_Quit();

	SDL_Quit();
}

void	Paint::initializeSDL(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL failed.");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	TTF_Init();
}

void	Paint::routineInit(void)
{
	int		value = 0;

	while (true)
	{
		value = _otherWindow->waitForEvent();

		if (value == 1)
			return ;

		if (value == 2)
		{
			delete _otherWindow;
			_otherWindow = nullptr;
			routine();
			return ;
		}

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}

void	Paint::routine(void)
{
	int		value = 0;

	while (true)
	{
		value = _mainWindow->waitForEvent();

		if (value == 1)
			return ;

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}
