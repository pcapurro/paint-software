#include "Paint.hpp"

int	Paint::getRandomNumber(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	return (rand());
}

void	Paint::randomizeColors(void)
{
	for (int i = 0; i != 20; i++)
	{
		_colorsUp.at(i).r = getRandomNumber() % 256;
		_colorsUp.at(i).g = getRandomNumber() % 256;
		_colorsUp.at(i).b = getRandomNumber() % 256;

		_colorsDown.at(i).r = getRandomNumber() % 256;
		_colorsDown.at(i).g = getRandomNumber() % 256;
		_colorsDown.at(i).b = getRandomNumber() % 256;
	}
}

void	Paint::display(void)
{
	SDL_Renderer*	renderer = _mainWindow->getRenderer();

	drawBackground(renderer);

	drawSaveCancel(renderer);
	drawTools(renderer);
	drawOptions(renderer);

	drawColorTools(renderer);
	drawColors(renderer);

	drawMap(renderer);

	_mainWindow->render();
}

bool	Paint::isOverZone(const int x, const int y)
{
	if (x >= 30 && x <= 160)
	{
		if (y >= 30 && y <= 95)
			return (true);
		
		if (y >= 160 && y <= 355)
			return (true);
	}

	if (x >= 30 && x <= 95 && y >= 390 && y <= 715)
		return (true);

	if (x >= 20 && x <= 85 && y >= 780 && y <= 870)
		return (true);

	if (x >= 115 && x <= 160 && y >= 780 && y <= 870)
		return (true);

	if (x >= 190 && x <= 240 && y >= 800 && y <= 850)
		return (true);

	return (false);
}

void	Paint::routine(void)
{
	SDL_Event	event;

	while (true)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ;

			int x = event.button.x;
			int y = event.button.y;

			if (x < 0 || x > _width || y < 0 || y > _height)
				continue ;

			if (isOverZone(x, y) == true)
				SDL_SetCursor(_interactCursor);
			else
				SDL_SetCursor(_normalCursor);
			
			display();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}
