#include "PaintSoftware.hpp"

int		PaintSoftware::waitForEvent(void)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_WaitEvent(&event) == 0)
	{
		throw std::runtime_error("SDL failed listening to events: " + \
			string(SDL_GetError()));
	}

	if (event.type == SDL_QUIT \
		|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		return END;

	if (event.type == SDL_MOUSEMOTION)
		x = event.motion.x, y = event.motion.y;
	else if (event.type == SDL_MOUSEBUTTONDOWN \
		|| event.type == SDL_MOUSEBUTTONUP)
		x = event.button.x, y = event.button.y;

	if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
		return OK;
	else
		setX(x), setY(y);

	reactEvent(&event, x, y);

	return OK;
}

int		PaintSoftware::routine(void)
{
    int     value = OK;

	render();
	refreshDisplay();

    while (true)
    {
        value = waitForEvent();

        if (value != OK)
            return value;
    }

    return OK;
}

void	PaintSoftware::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (!renderer)
		return;

	_paintFrame->render(renderer);

	_mainBox->render(renderer);
	_toolBox->render(renderer);

	if (_leftEndLine)
		_leftEndLine->render(renderer);
}
