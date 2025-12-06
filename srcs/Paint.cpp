#include "Paint.hpp"

Paint::~Paint(void)
{
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

void	Paint::start(void)
{
	auto 	mainWindow = std::make_shared<Software>(MAIN_TITLE, PAINT_W, PAINT_H);
	auto	welcomeWindow = std::make_shared<Ok>(WELCOME_TITLE, WELCOME_DESC);

	mainWindow.get()->draw();
	mainWindow.get()->blur();
	mainWindow.get()->render();

	std::thread	t2(&Ok::routine, welcomeWindow);
	t2.join();

	welcomeWindow.reset();

	std::thread	t1(&Software::routine, mainWindow);
	t1.join();
}
