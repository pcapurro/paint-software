#ifndef PAINTFRAME_HPP
# define PAINTFRAME_HPP

# include "Element.hpp"
# include "Shape.hpp"

class PaintFrame : public Element
{
    private:
        Shape           _frame;
        vector<Shape>   _pngBack;

        void            initPngBack(void);

    public:
        PaintFrame(void) = delete;
        PaintFrame(const int x, const int y, const int width, \
            const int height, Color& defaultColor);

        ~PaintFrame(void) = default;

        void            render(SDL_Renderer* renderer);
};

#endif
