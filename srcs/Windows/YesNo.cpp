#include "YesNo.hpp"

YesNo::YesNo(const std::string name, const std::string text) : Window(name, 400, 200)
{
	_text = text;

	setX(0);
	setY(0);

	_state = 0;

	SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

	loadFont();
}

void	YesNo::generateElements(void)
{
	;
}

void	YesNo::loadFont(void)
{
	_font = TTF_OpenFont("materials/font/OpenSans.ttf", 24);
	if (_font == NULL)
		throw std::runtime_error("SDL failed.");
}

void	YesNo::draw(void)
{
	SDL_Renderer*	renderer = getRenderer();

	drawBackground({42, 42, 42, 255});
	drawElements(&_elements);

	(void) renderer;
}

void	YesNo::reactEvent(SDL_Event* event)
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
			if (type == YES)
				_state = 2;
			if (type == NO)
				_state = 1;
		}
	}
}

int	YesNo::waitForEvent(void)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		if (event.type == SDL_QUIT \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (1);

		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RETURN \
			|| event.key.keysym.sym == SDLK_KP_ENTER))
			return (2);

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
			SDL_SetCursor(getCursor(value));
		else
			SDL_SetCursor(getCursor(0));

		if (event.type == SDL_MOUSEBUTTONDOWN \
			|| event.type == SDL_MOUSEBUTTONUP)
			reactEvent(&event);

		clear();
		draw();
		render();
	}

	return (_state);
}
