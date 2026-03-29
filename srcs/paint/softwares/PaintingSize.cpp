#include "PaintingSize.hpp"

PaintingSize::PaintingSize(void)
{
	_window.emplace(
		"Create a new painting",
		"materials/font/OpenSans.ttf",
		400, 170,
		Window::LightMode,
		"Painting size",
		true,
		"Specify width and height of your painting.",
		4,
		vector<string>{"width:", "height:"},
		vector<string>{"px", "px"},
		vector<int>{PaintView::MinPaintWidth, PaintView::MinPaintHeight},
		vector<int>{PaintView::MaxPaintWidth, PaintView::MaxPaintHeight}
	);

    _values.reserve(2);

	_values.push_back(PaintView::MaxPaintWidth);
	_values.push_back(PaintView::MaxPaintHeight);
}

vector<int>     PaintingSize::getValues(void) const
{
    return _values;
}

int     PaintingSize::routine(void)
{
	int			        value = State::Ok;
	SDL_Event	        lastEvent;

	while (value == State::Ok)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			value = _window->reactEvent(&lastEvent);

			if (value == State::Return)
			{
				if (!_window->error())
				{
					_values = _window->getFinalValues();

					if (!_values[0])
						_values[0] = PaintView::MaxPaintWidth;
					if (!_values[1])
						_values[1] = PaintView::MaxPaintHeight;
				}
				else
					value = State::Ok;
			}
		}

		_window->render();
		_window->refreshDisplay();

		SDL_Delay(16);
	}

    return value;
}
