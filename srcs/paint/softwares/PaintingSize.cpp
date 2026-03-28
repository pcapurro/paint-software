#include "PaintingSize.hpp"

PaintingSize::PaintingSize(void)
{
	_window.emplace(
		"Create a new painting",
		"materials/font/OpenSans.ttf",
		400, 170,
		LIGHT_MODE,
		"Painting size",
		true,
		"Specify width and height of your painting.",
		4,
		vector<string>{"width:", "height:"},
		vector<string>{"px", "px"},
		vector<int>{DEF_MIN_PAINT_W, DEF_MIN_PAINT_H},
		vector<int>{DEF_MAX_PAINT_W, DEF_MAX_PAINT_H}
	);

    _values.reserve(2);

	_values.push_back(DEF_MAX_PAINT_W);
	_values.push_back(DEF_MAX_PAINT_H);
}

vector<int>     PaintingSize::getValues(void) const
{
    return _values;
}

int     PaintingSize::routine(void)
{
	int			        value = OK;
	SDL_Event	        lastEvent;

	while (value == OK)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			value = _window->reactEvent(&lastEvent);

			if (value == RETURN)
			{
				if (!_window->error())
				{
					_values = _window->getFinalValues();

					if (!_values[0])
						_values[0] = DEF_MAX_PAINT_W;
					if (!_values[1])
						_values[1] = DEF_MAX_PAINT_H;
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
