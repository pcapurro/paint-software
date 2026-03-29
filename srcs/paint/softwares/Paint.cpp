#include "Paint.hpp"

Paint::Paint(const string& projectName, const int globalWidth, \
	const int globalHeight, const int paintWidth, const int paintHeight)
{
	_paint.emplace("paint-software – " + projectName, globalWidth, \
		globalHeight, paintWidth, paintHeight);

	// ...
}

int     Paint::routine(void)
{
	SDL_Event       lastEvent;
	int             value = State::Ok;

	vector<Window*>	windows;

	windows.reserve(4);
	windows.push_back(&_paint.value());

	while (value == State::Ok)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			int	windowId = lastEvent.window.windowID;

			for (auto& window : windows)
			{
				if (windowId != window->getWindowId())
					continue;

				value = window->reactEvent(&lastEvent);

				if (value == State::End && windowId == _paint->getWindowId())
					return value;

				// ...
			}
		}

		for (auto& window : windows)
			window->render(), window->refreshDisplay();

		SDL_Delay(16);
	}

    return value;
}
