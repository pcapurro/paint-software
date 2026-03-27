#include "Global.hpp"

#include "Engine.hpp"
#include "DialogValuesBox.hpp"
#include "DialogTextBox.hpp"

#include "PaintSoftware.hpp"
#include "ColorSelection.hpp"

void    getProjectName(string& projectName)
{
	DialogTextBox	window(
		"Create a new painting",
		"materials/font/OpenSans.ttf",
		400, 170,
		LIGHT_MODE,
		"Project name",
		true,
		"Specify the name of the project.",
		30
	);

	int			value = OK;
	string		newName;

	SDL_Event	lastEvent;

	while (value == OK)
	{
		while (SDL_PollEvent(&lastEvent))
			value = window.reactEvent(&lastEvent);

		window.render();
		window.refreshDisplay();

		SDL_Delay(16);

		if (value == OK)
			continue;

		newName = window.getFinalAnswer();
		if (newName.size() > 0)
			projectName = newName;
	}
}

void	getPaintingSize(int& paintWidth, int& paintHeight)
{
	DialogValuesBox		window(
		"Create a new painting",
		"materials/font/OpenSans.ttf",
		400, 170,
		LIGHT_MODE,
		"Painting size",
		true,
		"Specify width and height of your painting.",
		4,
		{"width:", "height:"},
		{"px", "px"},
		{50, 50},
		{DEF_MAX_PAINT_W, DEF_MAX_PAINT_H}
	);

	int			value = OK;

	string		newName;
	SDL_Event	lastEvent;

	while (value == OK)
	{
		while (SDL_PollEvent(&lastEvent))
			value = window.reactEvent(&lastEvent);

		window.render();
		window.refreshDisplay();

		SDL_Delay(16);

		if (value == OK)
			continue;

		if (value != END)
		{
			vector<int>	values = window.getFinalValues();

			if (!values[0] || !values[1])
				return;

			paintWidth = values[0];
			paintHeight = values[1];
		}
	}
}

void	launch(const string& projectName, const int globalWidth, \
	const int globalHeight, const int paintWidth, const int paintHeight)
{
	PaintSoftware				paintWindow("paint-software – " + projectName, \
		globalWidth, globalHeight, paintWidth, paintHeight);
	optional<ColorSelection>	colorWindow, cancelWindow, saveWindow;

	vector<Window*>				windows;

	SDL_Event					lastEvent;
	int							value = OK;

	windows.reserve(4);
	windows.push_back(&paintWindow);

	while (value == OK)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			int	windowId = lastEvent.window.windowID;

			for (auto& window : windows)
			{
				if (windowId != window->getWindowId())
					continue;

				value = window->reactEvent(&lastEvent);

				if (value == END && windowId == paintWindow.getWindowId())
					return;
			}
		}

		for (auto& window : windows)
			window->render(), window->refreshDisplay();

		SDL_Delay(16);
	}
}

int		main(void)
{
	try
	{
		Engine	engine(true, true, true, \
			true, true, false);

		string	projectName = "untitled";

		getProjectName(projectName);

		int		paintWidth = DEF_MAX_PAINT_W;
		int		paintHeight = DEF_MAX_PAINT_H;

		getPaintingSize(paintWidth, paintHeight);

		int		globalWidth = paintWidth + DEF_LEFT_W + DEF_RIGHT_W;
		int		globalHeight = paintHeight + DEF_UP_H + DEF_DOWN_H;

		launch(projectName, globalWidth < DEF_MIN_W ? DEF_MIN_W : globalWidth, \
			globalHeight < DEF_MIN_H ? DEF_MIN_H : globalHeight, paintWidth, paintHeight);
	}
	catch (std::exception& except)
	{
		cerr << RED_TXT << "Error! ";
		cerr << except.what() << END_COLOR << endl;

		return 1;
	}
	catch (...)
	{
		cerr << "Unknown error" << endl;

		return 1;
	}

	return 0;
}
