#include "Paint.hpp"

void	Paint::drawBackground(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.x = 0, obj.y = 0;
	obj.w = _width, obj.h = _height;

	_mainWindow->clear();

	SDL_SetRenderDrawColor(renderer, 42, 42, 42, 255);
	SDL_RenderFillRect(renderer, &obj);
}

void	Paint::drawToolBoxes(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.x = 30, obj.y = 30;
	obj.w = 130, obj.h = 840;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &obj);

	obj.x = 190, obj.y = 780;
	obj.w = 1280, obj.h = 90;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &obj);
}

void	Paint::drawMap(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.x = 190, obj.y = 30;
	obj.w = 1280, obj.h = 720;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &obj);
}

void	Paint::display(void)
{
	drawBackground(_mainWindow->getRenderer());
	drawToolBoxes(_mainWindow->getRenderer());

	drawMap(_mainWindow->getRenderer());

	_mainWindow->render();
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
			
			display();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}
