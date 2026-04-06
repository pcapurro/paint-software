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

        optional<PaintView>         _paint;

        optional<ColorSelection>    _colorSelection;
        optional<DialogBox>         _cancel;

    public:
        Paint(const string& projectName, const int globalWidth, \
	        const int globalHeight, const int paintWidth, const int paintHeight, \
            const int displayMode = Window::LightMode);

        ~Paint(void) = default;

        int         routine(void);
};

#endif
