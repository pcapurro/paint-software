#include "OkCancel.hpp"

OkCancel::OkCancel(const std::string name) : Window(name, 400, 200)
{
	_x = 0;
	_y = 0;

	_state = 0;

	SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

	loadFont();
}

void	OkCancel::generateElements(void)
{
	;
}

void	OkCancel::loadFont(void)
{
	_font = TTF_OpenFont("materials/font/OpenSans.ttf", 24);
	if (_font == NULL)
		throw std::runtime_error("SDL failed.");
}

void	OkCancel::draw(void)
{
	SDL_Renderer*	renderer = getRenderer();

	drawBackground({42, 42, 42, 255});
	drawElements(&_elements);

	(void) renderer;
}

void	OkCancel::reactEvent(SDL_Event* event)
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
			if (type == OK)
				_state = 2;
			if (type == CANCEL)
				_state = 1;
		}
	}
}

int	OkCancel::waitForEvent(void)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		cout << event.type << endl;

		if (event.type == SDL_QUIT || event.window.event == SDL_WINDOWEVENT_CLOSE
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (1);

		if (event.type == SDL_KEYDOWN \
			&& event.key.keysym.sym == SDLK_RETURN)
			return (2);

		int x = event.button.x;
		int y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return (0);

		// std::cout << _x << " ; " << _y << std::endl;

		int value = isOverZone(&_elements, _x, _y);

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
