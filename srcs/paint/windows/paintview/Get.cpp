#include "PaintView.hpp"

bool    PaintView::hasAlpha(void) const
{
    return _paintFrame->hasAlpha();
}

vector<vector<Color>>   PaintView::getPainting(void) const
{
    return _paintFrame->getPainting();
}

vector<Uint32>  PaintView::getPaintingPixels(void) const
{
    return _paintFrame->getPaintingPixels();
}
