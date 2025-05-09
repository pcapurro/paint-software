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

void	Paint::drawSaveCancel(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	obj.x = 30, obj.y = 30;
	obj.w = 130, obj.h = 65;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 127;
	obj.w = 130, obj.h = 4;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 160;
	obj.w = 130, obj.h = 195;

	SDL_RenderFillRect(renderer, &obj);

	obj.w = 65, obj.h = 65;

	obj.x = 30, obj.y = 30;
	SDL_RenderCopy(renderer, _textures.check.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 30;
	SDL_RenderCopy(renderer, _textures.cancel.getTexture(), NULL, &obj);
}

void	Paint::drawTools(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.w = 65, obj.h = 65;

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
}

void	Paint::drawOptions(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	obj.x = 30, obj.y = 390;
	obj.w = 130, obj.h = 325;

	SDL_RenderFillRect(renderer, &obj);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	obj.x = 34, obj.y = 394;
	obj.w = 122, obj.h = 317;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 746;
	obj.w = 130, obj.h = 4;

	SDL_RenderFillRect(renderer, &obj);
}

void	Paint::drawColorTools(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.x = 30, obj.y = 746;
	obj.w = 130, obj.h = 4;

	SDL_RenderFillRect(renderer, &obj);

	SDL_SetRenderDrawColor(renderer, _currentColor.r, _currentColor.g, \
		_currentColor.b, _currentColor.a);

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

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 194, obj.y = 804;
	obj.w = 42, obj.h = 42;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderFillRect(renderer, &obj);

	obj.w = 44, obj.h = 44;
	obj.x = 215 - obj.w / 2, obj.y = 825 - obj.h / 2;

	SDL_RenderCopy(renderer, _textures.random.getTexture(), NULL, &obj);
}

void	Paint::drawColors(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.x = 250, obj.y = 780;
	obj.w = 61, obj.h = 45;

	for (int i = 0; i != 20; i++)
	{
		SDL_SetRenderDrawColor(renderer, _colorsUp.at(i).r, \
			_colorsUp.at(i).g, _colorsUp.at(i).b, 255);
		SDL_RenderFillRect(renderer, &obj);

		obj.y += 45;

		SDL_SetRenderDrawColor(renderer, _colorsDown.at(i).r, \
			_colorsDown.at(i).g, _colorsDown.at(i).b, 255);
		SDL_RenderFillRect(renderer, &obj);

		obj.x += 61;
		obj.y -= 45;
	}
}

void	Paint::drawMap(SDL_Renderer* renderer)
{
	SDL_Rect		obj;

	obj.x = 190, obj.y = 30;
	obj.w = 1280, obj.h = 720;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &obj);
}
