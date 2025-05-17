#include "Software.hpp"

Software::Software(const std::string name, const int width, const int height) : Window(name, width, height)
{
	setX(0);
	setY(0);

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

	_elements.push_back(Element(30, 30, 65, 65, _icons.check.getTexture(), {255, 255, 255, 255}, CHECK));
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

	w = 50, h = 1;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 519 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 2;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 551 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 4;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 583 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 8;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 615 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 32, h = 32;
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 519 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_A, true, 1, false));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 551 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_B, true, 1, true));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 583 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_C, true, 1, false));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 615 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_D, true, 1, false));

	// colors tools

	_elements.push_back(Element(115, 780, 45, 45, NULL, {0, 0, 0, 255}, BLACK, true));
	_elements.push_back(Element(115, 825, 45, 45, NULL, {255, 255, 255, 255}, WHITE, true));

	_elements.push_back(Element(375, 800, 50, 50, NULL, {0, 0, 0, 255}));
	_elements.push_back(Element(379, 804, 42, 42, NULL, {255, 255, 255, 255}));

	w = 44, h = 44;
	_elements.push_back(Element(400 - (w / 2), 825 - (h / 2), w, h, _icons.random.getTexture(), {255, 255, 255, 255}, RANDOM, true));

	// rgba

	h = 25;

	_elements.push_back(Element(190, 792, w, h, NULL, {0, 0, 0, 255}, R, true, 3));
	_elements.push_back(Element(192, 794, w - 4, h - 4, NULL, {255, 255, 255, 255}, R, false));

	_elements.push_back(Element(244, 792, w, h, NULL, {0, 0, 0, 255}, G, true, 3));
	_elements.push_back(Element(246, 794, w - 4, h - 4, NULL, {255, 255, 255, 255}, G, false));

	_elements.push_back(Element(298, 792, w, h, NULL, {0, 0, 0, 255}, B, true, 3));
	_elements.push_back(Element(300, 794, w - 4, h - 4, NULL, {255, 255, 255, 255}, B, false));

	_elements.push_back(Element(244, 842, w, h, NULL, {0, 0, 0, 255}, A, true, 3));
	_elements.push_back(Element(246, 844, w - 4, h - 4, NULL, {255, 255, 255, 255}, A, false));

	w = 18;
	_elements.push_back(Element(203, 768, 18, 25, _icons.r.getTexture(), {0, 0, 0, 255}, R, false));
	_elements.push_back(Element(257, 768, 18, 25, _icons.g.getTexture(), {0, 0, 0, 255}, G, false));
	_elements.push_back(Element(311, 768, 18, 25, _icons.b.getTexture(), {0, 0, 0, 255}, B, false));
	_elements.push_back(Element(257, 818, 18, 25, _icons.a.getTexture(), {0, 0, 0, 255}, A, false));

	// colors

	int x = 0;
	int y = 0;

	x = 433, y = 780;
	w = 61, h = 45;

	for (int i = 0; i != 17; i++)
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

	value += _icons.check.loadTexture("materials/icons/check.bmp", renderer);
	value += _icons.cancel.loadTexture("materials/icons/cancel.bmp", renderer);

	value += _icons.left.loadTexture("materials/icons/left.bmp", renderer);
	value += _icons.right.loadTexture("materials/icons/right.bmp", renderer);

	value += _icons.brush.loadTexture("materials/icons/brush.bmp", renderer);
	value += _icons.pencil.loadTexture("materials/icons/pencil.bmp", renderer);

	value += _icons.spray.loadTexture("materials/icons/spray.bmp", renderer);
	value += _icons.bucket.loadTexture("materials/icons/bucket.bmp", renderer);

	value += _icons.picker.loadTexture("materials/icons/picker.bmp", renderer);
	value += _icons.eraser.loadTexture("materials/icons/eraser.bmp", renderer);

	value += _icons.line.loadTexture("materials/icons/line.bmp", renderer);
	value += _icons.text.loadTexture("materials/icons/text.bmp", renderer);

	value += _icons.random.loadTexture("materials/icons/random.bmp", renderer);
	value += _icons.select.loadTexture("materials/icons/select.bmp", renderer);

	value += _icons.r.loadText("R", _font, {255, 255, 255, 255}, renderer);
	value += _icons.g.loadText("G", _font, {255, 255, 255, 255}, renderer);
	value += _icons.b.loadText("B", _font, {255, 255, 255, 255}, renderer);
	value += _icons.a.loadText("A", _font, {255, 255, 255, 255}, renderer);

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

void	Software::setOption(void)
{
	Element*	element1 = NULL;
	Element*	element2 = NULL;
	Element*	element3 = NULL;
	Element*	element4 = NULL;

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
			else if (element4 == NULL)
				element4 = &_elements.at(i);
		}
	}

	element1->setVisibility(false);
	element2->setVisibility(false);
	element3->setVisibility(false);
	element4->setVisibility(false);

	if (_brushType == 1)
		element1->setVisibility(true);
	else if (_brushType == 2)
		element2->setVisibility(true);
	else if (_brushType == 3)
		element3->setVisibility(true);
	else if (_brushType == 4)
		element4->setVisibility(true);
}

void	Software::drawHighlight(SDL_Renderer* renderer)
{
	int			x = getX(), y = getY();
	SDL_Rect	obj;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 121);

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).isAbove(x, y) == true)
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

	drawBackground({42, 42, 42, 255});
	drawElements(&_elements);

	if (_highlight == true)
		drawHighlight(renderer);

	drawMap(renderer);
}

void	Software::reactEvent(SDL_Event* event)
{
	int			x = getX(), y = getY();
	Element*	element = NULL;

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).isAbove(x, y) == true)
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
			if (type == BRUSH_D)
				_brushType = 4, setOption();

			if (type == COLORS)
				changeColor(element->getColor());
		}
	}
}

int		Software::waitForEvent(void)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		if (event.type == SDL_QUIT \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (1);

		x = event.button.x;
		y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return (0);
		else
			setX(x), setY(y);

		// cout << event.button.x << " ; " << event.button.y << endl;
		// cout << x << " ; " << y << endl;

		int value = isOverZone(&_elements, x, y);

		if (value != 0)
			SDL_SetCursor(getCursor(value)), _highlight = true;
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
