#ifndef BRUSHOPTIONS_HPP
# define BRUSHOPTIONS_HPP

# include "Element.hpp"
# include "Shape.hpp"
# include "ImageButton.hpp"

class BrushOptions : public Element
{
    private:
        optional<Shape>             _background;

        size_t                      _brushValue = 1;
        vector<Shape>               _brushLines;
        vector<Shape>               _brushCursors;
        unique_ptr<ImageButton>     _selectedBrush;

        size_t                      _opacityValue = 100;
        optional<Shape>             _opacityBox;
        optional<Shape>             _opacityLine;
        optional<Shape>             _opacityCursor;

        void                        initBrushLines(SDL_Renderer* renderer);
        void                        initOpacity(void);

        void                        refreshBrush(SDL_Renderer* renderer);
        void                        refreshOpacity(const int x, const int y);

    public:
        BrushOptions(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~BrushOptions(void) = default;

        int                         getBrush(void) const noexcept;
        int                         getOpacity(void) const noexcept;

        void                        render(SDL_Renderer* renderer);

		virtual void	            onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

        virtual void	            onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void	            onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	            onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
