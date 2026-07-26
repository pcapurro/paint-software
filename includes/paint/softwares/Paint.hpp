#ifndef PAINT_HPP
# define PAINT_HPP

# include "Software.hpp"

# include "PaintView.hpp"
# include "ColorSelection.hpp"
# include "DialogBox.hpp"

class Paint : public Software
{
    private:
        const int                   _displayMode;

        string                      _projectName;

        int                         _paintWidth;
        int                         _paintHeight;

        optional<PaintView>         _paint;

        optional<ColorSelection>    _colorSelection;
        optional<DialogBox>         _save;
        optional<DialogBox>         _cancel;

        int                         savePainting(const vector<Uint32>& painting) const;

    public:
        Paint(const string& projectName, const int globalWidth, \
	        const int globalHeight, const int paintWidth, const int paintHeight, \
            const int displayMode = Window::LightMode);

        ~Paint(void) = default;

        int         routine(void);
};

#endif
