#ifndef PAINTFRAME_HPP
# define PAINTFRAME_HPP

# include "Element.hpp"
# include "Shape.hpp"

class PaintFrame : public Element
{
    private:
        Shape                   _frame;
        vector<Shape>           _pngBack;

		static constexpr int	PngWidth = 30;
		static constexpr int	PngHeight = 30;

        void                    initPngBack(void);

    public:
        PaintFrame(const int x, const int y, const int width, \
            const int height, Color& defaultColor);

        ~PaintFrame(void) = default;

        void                    render(SDL_Renderer* renderer);

        virtual void            onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void            onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void            onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void            onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
