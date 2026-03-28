#include "Global.hpp"

#include "Engine.hpp"

#include "Paint.hpp"
#include "PaintingSize.hpp"
#include "ProjectName.hpp"

#include "DialogBoxPreview.hpp"
#include "DialogTextBoxPreview.hpp"
#include "DialogValuesBoxPreview.hpp"

void    getProjectName(string& projectName)
{
	ProjectName		projectWindow;

	projectWindow.routine();
	projectName = projectWindow.getName();
}

void	getPaintingSize(int& paintWidth, int& paintHeight)
{
	vector<int>		paintingSizes;
	PaintingSize	paintingSizeWindow;

	paintingSizeWindow.routine();
	paintingSizes = paintingSizeWindow.getValues();

	paintWidth = paintingSizes[0];
	paintHeight = paintingSizes[1];
}

void    launch(const string& projectName, const int globalWidth, \
	const int globalHeight, const int paintWidth, const int paintHeight)
{
	Paint	paintWindow(projectName, globalWidth < DEF_MIN_W ? DEF_MIN_W : globalWidth, \
		globalHeight < DEF_MIN_H ? DEF_MIN_H : globalHeight, paintWidth, paintHeight);

	paintWindow.routine();
}

int		main(void)
{
	try
	{
		Engine	engine(true, true, true, \
			true, true, false);

		string	projectName;

		getProjectName(projectName);

		int		paintWidth = DEF_MAX_PAINT_W;
		int		paintHeight = DEF_MAX_PAINT_H;

		getPaintingSize(paintWidth, paintHeight);

		int		globalWidth = paintWidth + DEF_LEFT_W + DEF_RIGHT_W;
		int		globalHeight = paintHeight + DEF_UP_H + DEF_DOWN_H;

		launch(projectName, globalWidth, globalHeight, \
			paintWidth, paintHeight);
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
