#ifndef BRUSHOPTIONS_HPP
# define BRUSHOPTIONS_HPP

# include "Element.hpp"
# include "Shape.hpp"
# include "ImageButton.hpp"

class BrushOptions : public Element
{
    private:
        optional<Shape>             _background;

        vector<Shape>               _brushLines;
        optional<Shape>             _opacityLine;

        size_t                      _brushCursor = 1;
        vector<Shape>               _brushCursors;
        unique_ptr<ImageButton>     _selectedBrush;

        size_t                      _opacityCursor = 4;
        vector<Shape>               _opacityCursors;

        void                        initBrushLines(const Color& writeColor, SDL_Renderer* renderer);
        void                        initOpacity(const Color& writeColor);

        void                        refreshBrush(void);
        void                        refreshOpacity(void);
        void	                    refresh(void);

    public:
        BrushOptions(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~BrushOptions(void) = default;

        void                        render(SDL_Renderer* renderer);
};

#endif
