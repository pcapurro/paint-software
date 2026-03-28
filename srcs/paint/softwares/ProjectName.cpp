#include "ProjectName.hpp"

ProjectName::ProjectName(void)
{
    _window.emplace(
        "Create a new painting",
		"materials/font/OpenSans.ttf",
		400, 170,
		LIGHT_MODE,
		"Project name",
		true,
		"Specify the name of the project.",
		30
    );
}

string  ProjectName::getName(void) const
{
    return _name;
}

int     ProjectName::routine(void)
{
	int			    value = OK;
	SDL_Event	    lastEvent;

	while (value == OK)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			value = _window->reactEvent(&lastEvent);

			if (value == RETURN)
			{
				if (!_window->error())
				{
					string	newName = _window->getFinalAnswer();

					if (newName.size() > 0)
						_name = _window->getFinalAnswer();
				}
				else
					value = OK;
			}
		}

		_window->render();
		_window->refreshDisplay();

		SDL_Delay(16);
	}

    return value;
}
