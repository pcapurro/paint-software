#include "Paint.hpp"

Paint::Paint(void)
{
	initializeSDL();

	_mainWindow = new Software("🎨 paint-software", 1500, 900);
}

Paint::~Paint(void)
{
	if (_mainWindow != nullptr)
		delete _mainWindow;

	TTF_Quit();

	SDL_Quit();
}

void	Paint::initializeSDL(void)
{
	_mainWindow = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL failed.");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	TTF_Init();
}

void	Paint::routine(void)
{
	int	value = 0;

	while (true)
	{
		value = _mainWindow->waitForEvent();
		
		if (value == -1)
			break ;

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}
