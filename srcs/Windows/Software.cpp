#include "Software.hpp"

Software::Software(const std::string name, const int width, const int height) : Window(name, width, height)
{
	setX(0);
	setY(0);

	_brushType = 2;
	_opacity = 255;

	_colorChanged = false;

	SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

	loadFont();
	loadImages();

	generateElements();

	_tool = BRUSH;
	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).getType() == BRUSH) {
			_elements.at(i).select();
			break ;
		}
	}

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

	w = 50, h = 1;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 519 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 2;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 551 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 4;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 583 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 50, h = 8;
	_elements.push_back(Element(95 + (65 / 2) - (w / 2), 615 + (24 - (h / 2)), w, h, NULL, {0, 0, 0, 255}));

	w = 32, h = 32;
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 519 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_A, true, 1, 1, false));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 551 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_B, true, 1, 1, true));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 583 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_C, true, 1, 1, false));
	_elements.push_back(Element(30 + 65 / 2 - (w / 2), 615 + (24 - (h / 2)), w, h, _icons.select.getTexture(), {255, 255, 255, 255}, BRUSH_D, true, 1, 1, false));

	w = 100, h = 4;
	_elements.push_back(Element(45, 685, w, h, NULL, {0, 0, 0, 255}));

	w = 10, h = 10;
	_elements.push_back(Element(70 - w, 687 - (h / 2), w, h, NULL, {0, 0, 0, 255}, OP_A, true, 1, 1, false));
	_elements.push_back(Element(95 - w, 687 - (h / 2), w, h, NULL, {0, 0, 0, 255}, OP_B, true, 1, 1, false));
	_elements.push_back(Element(120 - w, 687 - (h / 2), w, h, NULL, {0, 0, 0, 255}, OP_C, true, 1, 1, false));
	_elements.push_back(Element(145 - w, 687 - (h / 2), w, h, NULL, {0, 0, 0, 255}, OP_D, true, 1, 1, true));

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
	_elements.push_back(Element(192, 794, w - 4, h - 4, NULL, {255, 255, 255, 255}));

	_elements.push_back(Element(244, 792, w, h, NULL, {0, 0, 0, 255}, G, true, 3));
	_elements.push_back(Element(246, 794, w - 4, h - 4, NULL, {255, 255, 255, 255}));

	_elements.push_back(Element(298, 792, w, h, NULL, {0, 0, 0, 255}, B, true, 3));
	_elements.push_back(Element(300, 794, w - 4, h - 4, NULL, {255, 255, 255, 255}));

	_elements.push_back(Element(244, 842, w, h, NULL, {0, 0, 0, 255}, A, true, 3));
	_elements.push_back(Element(246, 844, w - 4, h - 4, NULL, {255, 255, 255, 255}));

	TTF_SetFontSize(_font, 21);
	
	TTF_SizeText(_font, "R", &w, &h);
	_elements.push_back(Element(212 - (w / 2), 793 - h, w, h, _icons.r.getTexture(), {0, 0, 0, 255}, R, false));
	TTF_SizeText(_font, "G", &w, &h);
	_elements.push_back(Element(266 - (w / 2), 793 - h, w, h, _icons.g.getTexture(), {0, 0, 0, 255}, G, false));
	TTF_SizeText(_font, "B", &w, &h);
	_elements.push_back(Element(320 - (w / 2), 793 - h, w, h, _icons.b.getTexture(), {0, 0, 0, 255}, B, false));
	TTF_SizeText(_font, "A", &w, &h);
	_elements.push_back(Element(266 - (w / 2), 843 - h, w, h, _icons.a.getTexture(), {0, 0, 0, 255}, A, false));

	TTF_SetFontSize(_font, 18);

	TTF_SizeText(_font, std::to_string(0).c_str(), &w, &h);

	_elements.push_back(Element(212 - (w / 2), 803 - (h / 2), w, h, _icons.rValue.getTexture(), {0, 0, 0, 255}, R_VALUE));
	_elements.push_back(Element(266 - (w / 2), 803 - (h / 2), w, h, _icons.gValue.getTexture(), {0, 0, 0, 255}, G_VALUE));
	_elements.push_back(Element(320 - (w / 2), 803 - (h / 2), w, h, _icons.bValue.getTexture(), {0, 0, 0, 255}, B_VALUE));

	TTF_SizeText(_font, std::to_string(255).c_str(), &w, &h);
	_elements.push_back(Element(266 - (w / 2), 853 - (h / 2), w, h, _icons.aValue.getTexture(), {0, 0, 0, 255}, A_VALUE));

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

	_elements.push_back(Element(30, 780, 65, 90, NULL, {255, 255, 255, 255}));
	_elements.push_back(Element(30, 780, 65, 90, NULL, {0, 0, 0, 255}, COLOR));
	_color = &_elements.at(_elements.size() - 1);
}

void	Software::loadImages(void)
{
	int				value = 0;
	SDL_Renderer*	renderer = getRenderer();

	value += _icons.check.loadImage("materials/icons/check.bmp", renderer);
	value += _icons.cancel.loadImage("materials/icons/cancel.bmp", renderer);

	value += _icons.left.loadImage("materials/icons/left.bmp", renderer);
	value += _icons.right.loadImage("materials/icons/right.bmp", renderer);

	value += _icons.brush.loadImage("materials/icons/brush.bmp", renderer);
	value += _icons.pencil.loadImage("materials/icons/pencil.bmp", renderer);

	value += _icons.spray.loadImage("materials/icons/spray.bmp", renderer);
	value += _icons.bucket.loadImage("materials/icons/bucket.bmp", renderer);

	value += _icons.picker.loadImage("materials/icons/picker.bmp", renderer);
	value += _icons.eraser.loadImage("materials/icons/eraser.bmp", renderer);

	value += _icons.line.loadImage("materials/icons/line.bmp", renderer);
	value += _icons.text.loadImage("materials/icons/text.bmp", renderer);

	value += _icons.random.loadImage("materials/icons/random.bmp", renderer);
	value += _icons.select.loadImage("materials/icons/select.bmp", renderer);

	value += _icons.r.loadText("R", _font, {255, 255, 255, 255}, renderer);
	value += _icons.g.loadText("G", _font, {255, 255, 255, 255}, renderer);
	value += _icons.b.loadText("B", _font, {255, 255, 255, 255}, renderer);
	value += _icons.a.loadText("A", _font, {255, 255, 255, 255}, renderer);

	value += _icons.rValue.loadText("0", _font, {0, 0, 0, 255}, renderer);
	value += _icons.gValue.loadText("0", _font, {0, 0, 0, 255}, renderer);
	value += _icons.bValue.loadText("0", _font, {0, 0, 0, 255}, renderer);
	value += _icons.aValue.loadText("255", _font, {0, 0, 0, 255}, renderer);

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
	_color->setColor(newColor);
	_color->setOpacity(_opacity);

	_colorChanged = true;
}

void	Software::setOpacity(const int type)
{
	Element*	element1 = NULL;
	Element*	element2 = NULL;
	Element*	element3 = NULL;
	Element*	element4 = NULL;

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).getType() >= OP_A && _elements.at(i).getType() <= OP_D)
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

	if (type <= OP_A)
		element1->setVisibility(true), _opacity = 63;
	else if (type <= OP_B)
		element2->setVisibility(true), _opacity = 127;
	else if (type <= OP_C)
		element3->setVisibility(true), _opacity = 191;
	else if (type <= OP_D)
		element4->setVisibility(true), _opacity = 255;

	Color	newColor = _color->getColor();

	newColor.a = _opacity;
	_color->setColor(newColor);

	_colorChanged = true;
}

void	Software::setBrushType(const int type)
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

	if (type == BRUSH_A)
		element1->setVisibility(true), _brushType = 1;
	else if (type == BRUSH_B)
		element2->setVisibility(true), _brushType = 2;
	else if (type == BRUSH_C)
		element3->setVisibility(true), _brushType = 3;
	else if (type == BRUSH_D)
		element4->setVisibility(true), _brushType = 4;
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
	drawMap(renderer);
}

void	Software::refreshRGB(void)
{
	Element	*r, *g, *b, *a;
	Color	color = _color->getColor();

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).getType() == R_VALUE)
			r = &_elements.at(i);
		else if (_elements.at(i).getType() == G_VALUE)
			g = &_elements.at(i);
		else if (_elements.at(i).getType() == B_VALUE)
			b = &_elements.at(i);
		else if (_elements.at(i).getType() == A_VALUE)
			a = &_elements.at(i);
	}

	_icons.rValue.setTexture(NULL, std::to_string(color.r).c_str(), _font, {0, 0, 0, 255}, getRenderer());
	_icons.gValue.setTexture(NULL, std::to_string(color.g).c_str(), _font, {0, 0, 0, 255}, getRenderer());
	_icons.bValue.setTexture(NULL, std::to_string(color.b).c_str(), _font, {0, 0, 0, 255}, getRenderer());
	_icons.aValue.setTexture(NULL, std::to_string(color.a).c_str(), _font, {0, 0, 0, 255}, getRenderer());

	r->setTexture(_icons.rValue.getTexture());
	g->setTexture(_icons.gValue.getTexture());
	b->setTexture(_icons.bValue.getTexture());
	a->setTexture(_icons.aValue.getTexture());

	int w = 0, h = 0;

	TTF_SetFontSize(_font, 18);

	TTF_SizeText(_font, std::to_string(color.r).c_str(), &w, &h);
	r->setW(w), r->setH(h);
	r->setX(212 - (w / 2)), r->setY(803 - (h / 2));

	TTF_SizeText(_font, std::to_string(color.g).c_str(), &w, &h);
	g->setW(w), g->setH(h);
	g->setX(266 - (w / 2)), g->setY(803 - (h / 2));

	TTF_SizeText(_font, std::to_string(color.b).c_str(), &w, &h);
	b->setW(w), b->setH(h);
	b->setX(320 - (w / 2)), b->setY(803 - (h / 2));

	TTF_SizeText(_font, std::to_string(color.a).c_str(), &w, &h);
	a->setW(w), a->setH(h);
	a->setX(266 - (w / 2)), a->setY(853 - (h / 2));

	_colorChanged = false;
}

int		Software::getKeyValue(const int key)
{
	if (key == SDLK_0 || key == SDLK_KP_0)
		return (0);
	else if (key == SDLK_1 || key == SDLK_KP_1)
		return (1);
	else if (key == SDLK_2 || key == SDLK_KP_2)
		return (2);
	else if (key == SDLK_3 || key == SDLK_KP_3)
		return (3);
	else if (key == SDLK_4 || key == SDLK_KP_4)
		return (4);
	else if (key == SDLK_5 || key == SDLK_KP_5)
		return (5);
	else if (key == SDLK_6 || key == SDLK_KP_6)
		return (6);
	else if (key == SDLK_7 || key == SDLK_KP_7)
		return (7);
	else if (key == SDLK_8 || key == SDLK_KP_8)
		return (8);
	else if (key == SDLK_9 || key == SDLK_KP_9)
		return (9);
	
	return (-1);
}

void	Software::deleteRGB(const int type)
{
	Color	color = _color->getColor();

	if (type == R)
		color.r = 0;
	if (type == G)
		color.g = 0;
	if (type == B)
		color.b = 0;
	if (type == A)
	{
		color.a = 0;
		_opacity = 0;
	}

	changeColor(color);
	_colorChanged = true;
}

void	Software::decreaseRGB(const int type)
{
	Color	color = _color->getColor();

	if (type == R)
		color.r = color.r / 10;
	if (type == G)
		color.g = color.g / 10;
	if (type == B)
		color.b = color.b / 10;
	if (type == A)
	{
		color.a = color.a / 10;
		_opacity = color.a;
	}

	changeColor(color);
	_colorChanged = true;
}

void	Software::increaseRGB(const int type, const int value)
{
	Color	color = _color->getColor();

	if (type == R && color.r <= 99)
		color.r = color.r * 10, color.r += value;
	if (type == G && color.g <= 99)
		color.g = color.g * 10, color.g += value;
	if (type == B && color.b <= 99)
		color.b = color.b * 10, color.b += value;
	if (type == A && color.a <= 99)
	{
		color.a = color.a * 10, color.a += value;
		_opacity = color.a;
	}

	if (color.r > 255 || color.g > 255 \
		|| color.b > 255 || color.a > 255)
		return ;

	changeColor(color);
	_colorChanged = true;
}

void	Software::unSelect(void)
{
	for (unsigned int i = 0; i != _elements.size(); i++)
		_elements.at(i).unSelect();
}

void	Software::unHighlight(void)
{
	for (unsigned int i = 0; i != _elements.size(); i++)
		_elements.at(i).unHighlight();
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

	if (element == NULL) {
		SDL_SetCursor(getCursor(0));
		return ;
	}
	else
		element->highlight();
	
	int type = element->getType();

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (type == RANDOM)
			randomizeColors();

		if (type == BLACK)
			changeColor({0, 0, 0, 255});
		if (type == WHITE)
			changeColor({255, 255, 255, 255});

		if (type >= BRUSH_A && type <= BRUSH_D)
			setBrushType(type);
		if (type >= OP_A && type <= OP_D)
			setOpacity(type);

		if (type >= BRUSH && type <= TEXT)
			unSelect(), element->select(), _tool = type;

		if (type == COLORS)
			changeColor(element->getColor());
	}

	if (event->type == SDL_KEYDOWN && type >= R && type <= A)
	{
		if (event->key.keysym.sym == SDLK_BACKSPACE)
			decreaseRGB(type);
		else if (event->key.keysym.sym == SDLK_DELETE)
			deleteRGB(type);
		
		int value = getKeyValue(event->key.keysym.sym);
		if (value != -1)
			increaseRGB(type, value);
	}

	if (event->type == SDL_MOUSEMOTION)
		SDL_SetCursor(getCursor(element->getHighlightCursor()));
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

		// cout << x << " ; " << y << endl;

		if (x >= 0 && x <= getWidth() && y >= 0 && y <= getHeight())
			setX(x), setY(y);

		unHighlight();
	
		reactEvent(&event);
		if (_colorChanged == true)
			refreshRGB();
		
		clear();
		draw();
		render();
	}

	return (0);
}
