#include "Paint.hpp"

Paint::Paint(const string& projectName, const int globalWidth, \
	const int globalHeight, const int paintWidth, const int paintHeight)
{
	_paint.emplace("paint-software – " + projectName, globalWidth, \
		globalHeight, paintWidth, paintHeight);
}

int     Paint::routine(void)
{
	SDL_Event       lastEvent;
	int             value = State::Ok;

	vector<Window*>	windows = { &_paint.value(), \
		nullptr, nullptr, nullptr };

	while (true)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			int	windowId = lastEvent.window.windowID;

			for (auto& window : windows)
			{
				if (!window || windowId != window->getWindowId())
					continue;

				value = window->reactEvent(&lastEvent);

				if (windowId == _paint->getWindowId())
				{
					if (value == State::End)
						return value;
					else if (value == PaintView::ColorSwitch && !_colorSelection)
					{
						_colorSelection.emplace("color selection", "materials/font/OpenSans.ttf", \
							400, 170, Window::LightMode, "Color selection", true, "Select a new color.");

						windows[1] = &_colorSelection.value();
					}
				}
				else if (_colorSelection && windowId == _colorSelection->getWindowId())
				{
					if (value == State::Return)
					{
						if (!_colorSelection->error())
						{
							Color	newColor = _colorSelection->getFinalColor();

							_paint->updateColor(newColor);
							_paint->updateOpacityFromValue(newColor.a);
						}
						else
							value = State::Ok;
					}

					if (value == State::End || value == State::Return)
						_colorSelection.reset(), windows[1] = nullptr;
				}
			}
		}

		for (auto& window : windows)
		{
			if (!window)
				continue;

			window->render();
			window->refreshDisplay();
		}

		SDL_Delay(16);
	}

    return value;
}
