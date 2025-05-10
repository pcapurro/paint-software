#include "Software.hpp"

Software::Software(const std::string name, const int width, const int height) : Window(name, width, height)
{
	loadTextures();
	generateColors();
}

void	Software::loadTextures(void)
{
	int				value = 0;
	SDL_Renderer*	renderer = getRenderer();

	value += _icons.brush.load("materials/brush.bmp", renderer);
	value += _icons.pencil.load("materials/pencil.bmp", renderer);

	value += _icons.spray.load("materials/spray.bmp", renderer);
	value += _icons.bucket.load("materials/bucket.bmp", renderer);

	value += _icons.picker.load("materials/picker.bmp", renderer);
	value += _icons.eraser.load("materials/eraser.bmp", renderer);

	value += _icons.check.load("materials/check.bmp", renderer);
	value += _icons.cancel.load("materials/cancel.bmp", renderer);

	value += _icons.random.load("materials/random.bmp", renderer);
	value += _icons.select.load("materials/select.bmp", renderer);

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}

void	Software::randomizeColors(void)
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

void	Software::generateColors(void)
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

bool	Software::isOverZone(const int x, const int y) const
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

void	Software::drawBackground(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = 0, obj.y = 0;
	obj.w = getWidth(), obj.h = getHeight();

	SDL_SetRenderDrawColor(renderer, 42, 42, 42, 255);
	SDL_RenderFillRect(renderer, &obj);
}

void	Software::drawSaveCancel(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

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
	SDL_RenderCopy(renderer, _icons.check.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 30;
	SDL_RenderCopy(renderer, _icons.cancel.getTexture(), NULL, &obj);
}

void	Software::drawTools(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.w = 65, obj.h = 65;

	obj.x = 30, obj.y = 160;
	SDL_RenderCopy(renderer, _icons.brush.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 160;
	SDL_RenderCopy(renderer, _icons.pencil.getTexture(), NULL, &obj);

	obj.x = 30, obj.y = 225;
	SDL_RenderCopy(renderer, _icons.bucket.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 225;
	SDL_RenderCopy(renderer, _icons.spray.getTexture(), NULL, &obj);

	obj.x = 30, obj.y = 290;
	SDL_RenderCopy(renderer, _icons.eraser.getTexture(), NULL, &obj);

	obj.x = 95, obj.y = 290;
	SDL_RenderCopy(renderer, _icons.picker.getTexture(), NULL, &obj);
}

void	Software::drawOptions(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

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

void	Software::drawColorTools(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

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

	SDL_RenderCopy(renderer, _icons.random.getTexture(), NULL, &obj);
}

void	Software::drawColors(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

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

void	Software::drawMap(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = 190, obj.y = 30;
	obj.w = 1280, obj.h = 720;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &obj);
}

void	Software::draw(void)
{
	SDL_Renderer*	renderer = getRenderer();

	drawBackground(renderer);

	drawSaveCancel(renderer);
	drawTools(renderer);
	drawOptions(renderer);

	drawColorTools(renderer);
	drawColors(renderer);

	drawMap(renderer);
}

int		Software::waitForEvent(void)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		if (event.type == SDL_QUIT \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (-1);

		int x = event.button.x;
		int y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return (0);

		if (isOverZone(x, y) == true)
			SDL_SetCursor(getCursor(1));
		else
			SDL_SetCursor(getCursor(0));
		
		clear();
		draw();
		render();
	}

	return (0);
}
