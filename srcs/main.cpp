#include "Global.hpp"

#include "Engine.hpp"
#include "DialogValuesBox.hpp"
#include "Paint.hpp"

void	getPaintingSize(int& paintWidth, int& paintHeight)
{
	DialogValuesBox     window(
		"Create a new painting...",
		"materials/font/OpenSans.ttf",
		400, 170,
		LIGHT_MODE,
		"Painting size",
		true,
		"Specify width and height of your painting.",
		4,
		{"width:", "height:"},
		{"px", "px"},
		{1, 1},
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

void	getWindowSize(const int paintWidth, const int paintHeight, \
    int& globalWidth, int& globalHeight)
{
	globalWidth = paintWidth + DEF_LEFT_W + DEF_RIGHT_W;
	globalHeight = paintHeight + DEF_UP_H + DEF_DOWN_H;

	if (globalWidth < DEF_MIN_W)
		globalWidth = DEF_MIN_W;

	if (globalHeight < DEF_MIN_H)
		globalHeight = DEF_MIN_H;
}

int		main(void)
{
	try
	{
		Engine	engine(true, true, true, \
			true, true, false);

		int		paintWidth = DEF_MAX_PAINT_W;
		int		paintHeight = DEF_MAX_PAINT_H;

		getPaintingSize(paintWidth, paintHeight);

		// cout << "Creating a painting of "
			// << paintWidth << "x" << paintHeight << endl;

		int		globalWidth = 0;
		int		globalHeight = 0;

		getWindowSize(paintWidth, paintHeight, \
			globalWidth, globalHeight);

		// cout << "Creating a window of "
			// << globalWidth << "x" << globalHeight << endl;

		Paint	paint("paint-software", globalWidth, globalHeight, \
			paintWidth, paintHeight);

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
