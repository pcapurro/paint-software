#include "Software.hpp"

Software::Software(const std::string name, const int width, const int height) : Window(name, width, height)
{
	_x = 0;
	_y = 0;

	_brushType = 2;
	_opacity = 100;

	_highlight = false;

	SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

	loadFont();
	loadTextures();

	generateElements();
	randomizeColors();
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

void	Software::generateElements(void)
{
	// save/cancel/left/right

	_elements.push_back(Element(30, 30, 130, 130, NULL, {255, 255, 255, 255}));

	_elements.push_back(Element(30, 30, 65, 65, _icons.check.getTexture(), {255, 255, 255, 255}, CHECK, true));
	_elements.push_back(Element(95, 30, 65, 65, _icons.cancel.getTexture(), {255, 255, 255, 255}, CANCEL, true));

	_elements.push_back(Element(30, 95, 65, 65, _icons.left.getTexture(), {255, 255, 255, 255}, LEFT, true));
	_elements.push_back(Element(95, 95, 65, 65, _icons.right.getTexture(), {255, 255, 255, 255}, RIGHT, true));

	_elements.push_back(Element(30, 191, 130, 4, NULL, {255, 255, 255, 255}));

	// tools

	_elements.push_back(Element(30, 226, 130, 260, NULL, {255, 255, 255, 255}));

	_elements.push_back(Element(30, 226, 65, 65, _icons.brush.getTexture(), {255, 255, 255, 255}, BRUSH, true));
	_elements.push_back(Element(95, 226, 65, 65, _icons.pencil.getTexture(), {255, 255, 255, 255}, PENCIL, true));

	_elements.push_back(Element(30, 291, 65, 65, _icons.bucket.getTexture(), {255, 255, 255, 255}, BUCKET, true));
	_elements.push_back(Element(95, 291, 65, 65, _icons.spray.getTexture(), {255, 255, 255, 255}, SPRAY, true));

	_elements.push_back(Element(30, 356, 65, 65, _icons.eraser.getTexture(), {255, 255, 255, 255}, ERASER, true));
	_elements.push_back(Element(95, 356, 65, 65, _icons.picker.getTexture(), {255, 255, 255, 255}, PICKER, true));

	_elements.push_back(Element(30, 421, 65, 65, _icons.line.getTexture(), {255, 255, 255, 255}, LINE, true));
	_elements.push_back(Element(95, 421, 65, 65, _icons.text.getTexture(), {255, 255, 255, 255}, TEXT, true));

	// options

	_elements.push_back(Element(30, 515, 130, 200, NULL, {0, 0, 0, 255}));
	_elements.push_back(Element(34, 519, 122, 192, NULL, {255, 255, 255, 255}));
	
	_elements.push_back(Element(30, 746, 130, 4, NULL, {255, 255, 255, 255}));

	int w = 0;
	int h = 0;

	w = 50, h = 2;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 519 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 4;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 567 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 8;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 615 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 32, h = 32;
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 519 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_A, true, false));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 567 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_B, true, true));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 615 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_C, true, false));

	// colors tools

	_elements.push_back(Element(115, 780, 45, 45, NULL, {0, 0, 0, 255}, BLACK, true));
	_elements.push_back(Element(115, 825, 45, 45, NULL, {255, 255, 255, 255}, WHITE, true));

	_elements.push_back(Element(190, 800, 50, 50, NULL, {0, 0, 0, 255}));
	_elements.push_back(Element(194, 804, 42, 42, NULL, {255, 255, 255, 255}));

	w = 44, h = 44;
	_elements.push_back(Element(215 - w / 2, 825 - h / 2, w, h, _icons.random.getTexture(), {255, 255, 255, 255}, RANDOM, true));

	// colors

	int x = 0;
	int y = 0;

	x = 250, y = 780;
	w = 61, h = 45;

	for (int i = 0; i != 20; i++)
	{
		_elements.push_back({x, y, w, h, NULL, {getRandomNumber() % 256, \
			getRandomNumber() % 256, getRandomNumber() % 256, 255}, COLORS, true});

		y += 45;

		_elements.push_back({x, y, w, h, NULL, {getRandomNumber() % 256, \
			getRandomNumber() % 256, getRandomNumber() % 256, 255}, COLORS, true});

		x += 61;
		y -= 45;
	}

	// color

	_elements.push_back(Element(30, 780, 65, 90, NULL, {0, 0, 0, 255}, COLOR));
	_currentColor = &_elements.at(_elements.size() - 1);
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
	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).getType() == COLORS)
		{
			_elements.at(i).setColor({getRandomNumber() % 256,
				getRandomNumber() % 256, getRandomNumber() % 256, 255});
		}
	}
}

void	Software::changeColor(Color newColor)
{
	_currentColor->setColor(newColor);
}

bool	Software::isOverZone(void) const
{
	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).isAbove(_x, _y) == true)
			return (true);
	}
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

void	Software::setOption(void)
{
	Element*	element1 = NULL;
	Element*	element2 = NULL;
	Element*	element3 = NULL;

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).getTexture() == _icons.select.getTexture())
		{
			if (element1 == NULL)
				element1 = &_elements.at(i);
			else if (element2 == NULL)
				element2 = &_elements.at(i);
			else if (element3 == NULL)
				element3 = &_elements.at(i);
		}
	}

	element1->setVisibility(false);
	element2->setVisibility(false);
	element3->setVisibility(false);

	if (_brushType == 1)
		element1->setVisibility(true);
	else if (_brushType == 2)
		element2->setVisibility(true);
	else if (_brushType == 3)
		element3->setVisibility(true);
}

void	Software::drawHighlight(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 121);

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).isAbove(_x, _y) == true)
		{
			obj.x = _elements.at(i).getX();
			obj.y = _elements.at(i).getY();
		
			obj.w = _elements.at(i).getW();
			obj.h = _elements.at(i).getH();
	
			break ;
		}
	}

	SDL_RenderFillRect(renderer, &obj);
}

void	Software::drawElements(SDL_Renderer* renderer)
{
	for (unsigned int i = 0; i != _elements.size(); i++)
		_elements.at(i).draw(renderer);
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
	drawElements(renderer);

	if (_highlight == true)
		drawHighlight(renderer);

	drawMap(renderer);
}

void	Software::reactEvent(SDL_Event* event)
{
	Element*	element = NULL;

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).isAbove(_x, _y) == true)
			element = &_elements.at(i);
	}

	if (element == NULL)
		return ;
	else
	{
		int type = element->getType();

		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			if (type == RANDOM)
				randomizeColors();

			if (type == BLACK)
				changeColor({0, 0, 0, 255});
			if (type == WHITE)
				changeColor({255, 255, 255, 255});

			if (type == BRUSH_A)
				_brushType = 1, setOption();
			if (type == BRUSH_B)
				_brushType = 2, setOption();
			if (type == BRUSH_C)
				_brushType = 3, setOption();

			if (type == COLORS)
				changeColor(element->getColor());
		}
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
			reactEvent(&event);
		
		clear();
		draw();
		render();
	}

	return (0);
}
