#ifndef PAINTFRAME_HPP
# define PAINTFRAME_HPP

# include "Shape.hpp"

class PaintFrame
{
    private:
        const int   _width;
        const int   _height;

    public:
        PaintFrame(void) = delete;
        PaintFrame(const int width, const int height);

        ~PaintFrame(void) = default;
};

#endif
