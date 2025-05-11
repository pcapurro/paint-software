#include "Software.hpp"

Software::Software(const std::string name, const int width, const int height) : Window(name, width, height)
{
	_x = 0;
	_y = 0;

	_brushType = 2;
	_opacity = 100;

	_highlight = false;

	loadFont();
	loadTextures();
	generateColors();
}

Software::~Software(void)
{
	if (_font != NULL && _font != nullptr)
		TTF_CloseFont(_font);
}

void	Software::loadFont(void)
{
	_font = TTF_OpenFont("materials/font/OpenSans.ttf", 24);
	if (_font == NULL)
		throw std::runtime_error("SDL failed.");
}

void	Software::loadTextures(void)
{
	int				value = 0;
	SDL_Renderer*	renderer = getRenderer();

	value += _icons.check.load("materials/icons/check.bmp", renderer);
	value += _icons.cancel.load("materials/icons/cancel.bmp", renderer);

	value += _icons.left.load("materials/icons/left.bmp", renderer);
	value += _icons.right.load("materials/icons/right.bmp", renderer);

	value += _icons.brush.load("materials/icons/brush.bmp", renderer);
	value += _icons.pencil.load("materials/icons/pencil.bmp", renderer);

	value += _icons.spray.load("materials/icons/spray.bmp", renderer);
	value += _icons.bucket.load("materials/icons/bucket.bmp", renderer);

	value += _icons.picker.load("materials/icons/picker.bmp", renderer);
	value += _icons.eraser.load("materials/icons/eraser.bmp", renderer);

	value += _icons.line.load("materials/icons/line.bmp", renderer);
	value += _icons.text.load("materials/icons/text.bmp", renderer);

	value += _icons.random.load("materials/icons/random.bmp", renderer);
	value += _icons.select.load("materials/icons/select.bmp", renderer);

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

void	Software::changeColor(Color newColor)
{
	_currentColor = newColor;
}

bool	Software::isOverZone(void) const
{
	// for (unsigned int i = 0; i != _boxes.size(); i++)
	// {
	// 	if (_x >= _boxes.at(i).x && _x <= _boxes.at(i).x + _boxes.at(i).w
	// 		&& _y >= _boxes.at(i).y && _y <= _boxes.at(i).y + _boxes.at(i).h)
	// 		return (true);
	// }

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
	obj.w = 130, obj.h = 130;

	SDL_RenderFillRect(renderer, &obj);

	obj.w = 65, obj.h = 65;

	obj.x = 30, obj.y = 30;
	SDL_RenderCopy(renderer, _icons.check.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 95, obj.y = 30;
	SDL_RenderCopy(renderer, _icons.cancel.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 30, obj.y = 95;
	SDL_RenderCopy(renderer, _icons.left.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 95, obj.y = 95;
	SDL_RenderCopy(renderer, _icons.right.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 30, obj.y = 191;
	obj.w = 130, obj.h = 4;

	SDL_RenderFillRect(renderer, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});
}

void	Software::drawTools(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = 30, obj.y = 226;
	obj.w = 130, obj.h = 260;

	SDL_RenderFillRect(renderer, &obj);

	obj.w = 65, obj.h = 65;

	obj.x = 30, obj.y = 226;
	SDL_RenderCopy(renderer, _icons.brush.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 95, obj.y = 226;
	SDL_RenderCopy(renderer, _icons.pencil.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 30, obj.y = 291;
	SDL_RenderCopy(renderer, _icons.bucket.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 95, obj.y = 291;
	SDL_RenderCopy(renderer, _icons.spray.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 30, obj.y = 356;
	SDL_RenderCopy(renderer, _icons.eraser.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 95, obj.y = 356;
	SDL_RenderCopy(renderer, _icons.picker.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 30, obj.y = 421;
	SDL_RenderCopy(renderer, _icons.line.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});

	obj.x = 95, obj.y = 421;
	SDL_RenderCopy(renderer, _icons.text.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, obj.y, obj.w, obj.h});
}

void	Software::drawOptions(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	obj.x = 30, obj.y = 515;
	obj.w = 130, obj.h = 200;

	SDL_RenderFillRect(renderer, &obj);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	obj.x = 34, obj.y = 519;
	obj.w = 122, obj.h = 192;

	SDL_RenderFillRect(renderer, &obj);

	obj.x = 30, obj.y = 746;
	obj.w = 130, obj.h = 4;

	SDL_RenderFillRect(renderer, &obj);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	obj.w = 50, obj.h = 2;
	obj.x = 95 + (65 / 2) - (obj.w / 2), obj.y = 519 + (24 - (obj.h / 2));

	SDL_RenderFillRect(renderer, &obj);

	obj.w = 50, obj.h = 4;
	obj.x = 95 + (65 / 2) - (obj.w / 2), obj.y = 567 + (24 - (obj.h / 2));

	SDL_RenderFillRect(renderer, &obj);

	obj.w = 50, obj.h = 8;
	obj.x = 95 + (65 / 2) - (obj.w / 2), obj.y = 615 + (24 - (obj.h / 2));

	SDL_RenderFillRect(renderer, &obj);

	obj.w = 32, obj.h = 32;
	obj.x = 30 + 65 / 2 - (obj.w / 2);

	if (_brushType == 1)
		obj.y = 519 + (24 - (obj.h / 2));
	else if (_brushType == 2)
		obj.y = 567 + (24 - (obj.h / 2));
	else if (_brushType == 3)
		obj.y = 615 + (24 - (obj.h / 2));

	SDL_RenderCopy(renderer, _icons.select.getTexture(), NULL, &obj);

	// _boxes.push_back({obj.x, 519 + (24 - (obj.h / 2)), obj.w, obj.h});
	// _boxes.push_back({obj.x, 567 + (24 - (obj.h / 2)), obj.w, obj.h});
	// _boxes.push_back({obj.x, obj.y = 615 + (24 - (obj.h / 2)), obj.w, obj.h});
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

void	Software::drawHighlight(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 121);

	if (_y < 750)
		obj.w = 65, obj.h = 65;
	else
	{
		if (_x <= 95)
			obj.w = 65, obj.h = 90;
		else if (_x >= 115 && _x <= 160)
			obj.w = 45, obj.h = 45;
		else if (_x >= 194 && _x <= 236)
			obj.w = 44, obj.h = 44;
		else
			obj.w = 61, obj.h = 45;
	}

	SDL_RenderFillRect(renderer, &obj);
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

	if (_highlight == true)
		drawHighlight(renderer);

	drawMap(renderer);
}

void	Software::reactEvent(SDL_Event* event, const int x, const int y)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (x >= 190 && x <= 240 && y >= 800 && y <= 850)
			randomizeColors();

		if (x >= 115 && x <= 160)
		{
			if (y > 780 && y < 825)
				changeColor({0, 0, 0, 255});
			if (y > 825 && y < 870)
				changeColor({255, 255, 255, 255});
		}

		if (x >= 30 && x <= 95)
		{
			if (y >= 519 && y <= 567)
				_brushType = 1;
			if (y >= 567 && y <= 615)
				_brushType = 2;
			if (y >= 615 && y <= 663)
				_brushType = 3;
		}
	}
	else
	{
		// ...
	}
}

int		Software::waitForEvent(void)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		if (event.type == SDL_QUIT \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (-1);

		_x = event.button.x;
		_y = event.button.y;

		if (_x < 0 || _x > getWidth() || _y < 0 || _y > getHeight())
			return (0);

		std::cout << _x << " ; " << _y << std::endl;

		if (isOverZone() == true)
			SDL_SetCursor(getCursor(1)), _highlight = true;
		else
			SDL_SetCursor(getCursor(0)), _highlight = false;

		if (event.type == SDL_MOUSEBUTTONDOWN \
			|| event.type == SDL_MOUSEBUTTONUP)
			reactEvent(&event, _x, _y);
		
		clear();
		draw();
		render();
	}

	return (0);
}
