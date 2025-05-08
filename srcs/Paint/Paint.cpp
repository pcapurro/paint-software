#include "Paint.hpp"

int	Paint::getRandomNumber(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	return (rand());
}

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

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	obj.x = 30, obj.y = 30;
	obj.w = 130, obj.h = 65;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 160;
	obj.w = 130, obj.h = 325;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 520;
	obj.w = 130, obj.h = 195;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 127;
	obj.w = 130, obj.h = 4;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 746;
	obj.w = 130, obj.h = 4;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 780;
	obj.w = 65, obj.h = 90;

	SDL_RenderFillRect(renderer, &obj);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	obj.x = 115, obj.y = 780;
	obj.w = 45, obj.h = 45;

	SDL_RenderFillRect(renderer, &obj);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	obj.x = 115, obj.y = 825;
	obj.w = 45, obj.h = 45;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 190, obj.y = 800;
	obj.w = 50, obj.h = 50;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 250, obj.y = 780;
	obj.w = 61, obj.h = 45;

	for (int i = 0; i != 20; i++)
	{
		SDL_SetRenderDrawColor(renderer, getRandomNumber(), getRandomNumber(), getRandomNumber(), 255);
		SDL_RenderFillRect(renderer, &obj);

		obj.y += 45;

		SDL_SetRenderDrawColor(renderer, getRandomNumber(), getRandomNumber(), getRandomNumber(), 255);
		SDL_RenderFillRect(renderer, &obj);

		obj.x += 61;
		obj.y -= 45;
	}
}

void	Paint::drawTools(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.w = 65, obj.h = 65;

	obj.x = 30, obj.y = 30;
	SDL_RenderCopy(renderer, _textures.check.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 30;
	SDL_RenderCopy(renderer, _textures.cancel.getTexture(), NULL, &obj);

	obj.x = 30, obj.y = 160;
	SDL_RenderCopy(renderer, _textures.brush.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 160;
	SDL_RenderCopy(renderer, _textures.pencil.getTexture(), NULL, &obj);

	obj.x = 30, obj.y = 225;
	SDL_RenderCopy(renderer, _textures.bucket.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 225;
	SDL_RenderCopy(renderer, _textures.spray.getTexture(), NULL, &obj);

	obj.x = 30, obj.y = 290;
	SDL_RenderCopy(renderer, _textures.eraser.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 290;
	SDL_RenderCopy(renderer, _textures.picker.getTexture(), NULL, &obj);

	obj.x = 190, obj.y = 800;
	obj.w = 50, obj.h = 50;

	SDL_RenderCopy(renderer, _textures.random.getTexture(), NULL, &obj);
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

	drawTools(_mainWindow->getRenderer());

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
