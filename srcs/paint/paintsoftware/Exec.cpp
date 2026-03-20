#include "PaintSoftware.hpp"

void    PaintSoftware::execMain(void)
{
    int     value = _mainBox->getLastButtonClicked();

    if (value == NONE)
        return;

    // if (value == SAVE)
    //     ;
    // else if (value == CANCEL)
    //     ;
    // else if (value == BACK)
    //     ;
    // else if (value == FORWARD)
    //     ;

    // ...
}

void    PaintSoftware::execTool(void)
{
    int     value = _toolBox->getSelectedTool();

    if (value == _selectedTool)
        return;

    _selectedTool = _toolBox->getSelectedTool();

    // ...
}

void	PaintSoftware::exec(void)
{
	execMain();
    execTool();
}
