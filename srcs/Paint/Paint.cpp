#include "Paint.hpp"

void	Paint::display(void)
{
	SDL_Renderer*	renderer = _mainWindow->getRenderer();
	SDL_Rect		obj;

	obj.x = 0, obj.y = 0;
	obj.w = _width, obj.h = _height;

	_mainWindow->clear();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &obj);

	obj.x = 25, obj.y = 25;
	obj.w = _width - 50, obj.h = 125;

	SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
	SDL_RenderFillRect(renderer, &obj);

	obj.x = 25, obj.y = 175;
	obj.w = _width - 50, obj.h = _height - 200;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &obj);

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
