#include "Global.hpp"

#include "Engine.hpp"

#include "Paint.hpp"
#include "PaintingSize.hpp"
#include "ProjectName.hpp"

#include "DialogBoxPreview.hpp"
#include "DialogTextBoxPreview.hpp"
#include "DialogValuesBoxPreview.hpp"

void	getDisplayMode(int& displayMode, int argc, char** argv)
{
	if (argc <= 1)
		return;

	for (int i = 0; argv[i] != NULL; i++)
	{
		if (string(argv[i]) == "-l" || string(argv[i]) == "--light-mode")
			displayMode = Window::LightMode;

		else if (string(argv[i]) == "-d" || string(argv[i]) == "--dark-mode")
			displayMode = Window::DarkMode;
	}
}

void    getProjectName(string& projectName, const int displayMode)
{
	ProjectName		projectWindow(displayMode);

	projectWindow.routine();
	projectName = projectWindow.getName();
}

void	getPaintingSize(int& paintWidth, int& paintHeight, const int displayMode)
{
	vector<int>		paintingSizes;
	PaintingSize	paintingSizeWindow(displayMode);

	paintingSizeWindow.routine();
	paintingSizes = paintingSizeWindow.getValues();

	paintWidth = paintingSizes[0];
	paintHeight = paintingSizes[1];
}

void    launch(const string& projectName, const int globalWidth, \
	const int globalHeight, const int paintWidth, const int paintHeight, \
	const int displayMode)
{
	int		width = globalWidth < PaintView::MinimumWidth ? PaintView::MinimumWidth : globalWidth;
	int		height = globalHeight < PaintView::MinimumHeight ? PaintView::MinimumHeight : globalHeight;

	Paint	paintWindow(projectName, width, height, \
		paintWidth, paintHeight, displayMode);

	paintWindow.routine();
}

int		main(int argc, char** argv)
{
	try
	{
		int		displayMode = Window::DarkMode;

		getDisplayMode(displayMode, argc, argv);

		Engine	engine(true, true, true, \
			true, true, false);

		string	projectName;

		getProjectName(projectName, displayMode);

		int		paintWidth = PaintView::MaxPaintWidth;
		int		paintHeight = PaintView::MaxPaintHeight;

		getPaintingSize(paintWidth, paintHeight, displayMode);

		int		globalWidth = paintWidth + \
			PaintView::LeftWidth + PaintView::RightWidth;
		int		globalHeight = paintHeight + \
			PaintView::UpHeight + PaintView::DownHeight;

		launch(projectName, globalWidth, globalHeight, \
			paintWidth, paintHeight, displayMode);
	}
	catch (std::exception& except)
	{
		cerr << "\033[31m" << "Error! ";
		cerr << except.what() << "\033[0m" << endl;

		return 1;
	}
	catch (...)
	{
		cerr << "Unknown error" << endl;

		return 1;
	}

	return 0;
}
