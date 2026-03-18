#ifndef BRUSHOPTIONS_HPP
# define BRUSHOPTIONS_HPP

# include "Element.hpp"
# include "Shape.hpp"
# include "ImageButton.hpp"

class BrushOptions : public Element
{
    private:
        optional<Shape>                     _background;

		vector<unique_ptr<ImageButton>>		_brushCursors;
		vector<Shape>						_opacityCursors;

        vector<Shape>                       _brushLines;
        optional<Shape>                     _opacityLine;

    public:
        BrushOptions(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~BrushOptions(void) = default;

        void        render(SDL_Renderer* renderer);
};

#endif
