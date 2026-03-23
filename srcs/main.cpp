#include "Global.hpp"

#include "Engine.hpp"

#include "DialogValuesBox.hpp"
#include "DialogTextBox.hpp"

#include "PaintSoftware.hpp"

void    getProjectName(string& projectName)
{
	DialogTextBox      window(
		"Create a new painting",
		"materials/font/OpenSans.ttf",
		400, 170,
		LIGHT_MODE,
		"Project name",
		true,
		"Specify the name of the project.",
		30
	);

	if (window.routine() == END)
		return;

	string	newName = window.getFinalAnswer();

	if (newName.size() > 0)
		projectName = window.getFinalAnswer();
}

void	getPaintingSize(int& paintWidth, int& paintHeight)
{
	DialogValuesBox     window(
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

	if (window.routine() == END)
		return;

	vector<int>		values = window.getFinalValues();

	if (values[0] == 0 || values[1] == 0)
		return;

	paintWidth = values[0];
	paintHeight = values[1];
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

		if (globalWidth < DEF_MIN_W)
			globalWidth = DEF_MIN_W;
		if (globalHeight < DEF_MIN_H)
			globalHeight = DEF_MIN_H;

		PaintSoftware	paint("paint-software – " + projectName, \
			globalWidth, globalHeight, paintWidth, paintHeight);

		paint.routine();
	}
	catch (std::exception& except)
	{
		cerr << "Error!" << endl;
		cerr << except.what() << endl;

		return 1;
	}
	catch (...)
	{
		cerr << "Unknown error" << endl;

		return 1;
	}

	return 0;
}
