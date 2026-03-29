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
	Paint	paintWindow(projectName, globalWidth < PaintView::MinimumWidth ? \
		PaintView::MinimumWidth : globalWidth, \
		globalHeight < PaintView::MinimumHeight ? PaintView::MinimumHeight : \
		globalHeight, paintWidth, paintHeight);

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

		int		paintWidth = PaintView::MaxPaintWidth;
		int		paintHeight = PaintView::MaxPaintHeight;

		getPaintingSize(paintWidth, paintHeight);

		int		globalWidth = paintWidth + \
			PaintView::LeftWidth + PaintView::RightWidth;
		int		globalHeight = paintHeight + \
			PaintView::UpHeight + PaintView::DownHeight;

		launch(projectName, globalWidth, globalHeight, \
			paintWidth, paintHeight);
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
