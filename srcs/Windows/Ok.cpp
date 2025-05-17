#include "Ok.hpp"

Ok::Ok(const std::string name) : Window(name, 400, 200)
{
	_x = 0;
	_y = 0;

	_state = 0;

	SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

	loadFont();
}

void	Ok::generateElements(void)
{
	;
}

void	Ok::loadFont(void)
{
	_font = TTF_OpenFont("materials/font/OpenSans.ttf", 24);
	if (_font == NULL)
		throw std::runtime_error("SDL failed.");
}

void	Ok::draw(void)
{
	SDL_Renderer*	renderer = getRenderer();

	drawBackground({0, 0, 0, 255});
	drawElements(&_elements);

	(void) renderer;
}

void	Ok::reactEvent(SDL_Event* event)
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
		if (event->type == SDL_MOUSEBUTTONDOWN)
			_state = 2;
	}
}

int	Ok::waitForEvent(void)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) \
			|| event.type == SDL_QUIT || event.window.event == SDL_WINDOWEVENT_CLOSE \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
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
