#include "OkCancel.hpp"

OkCancel::OkCancel(const std::string name) : Window(name, 200, 70)
{
	(void) name;
}

int	OkCancel::waitForEvent(void)
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

		// if (isOverZone() == true)
			// SDL_SetCursor(getCursor(1));
		// else
			// SDL_SetCursor(getCursor(0));
		
		clear();
		draw();
		render();
	}

	return (0);
}
