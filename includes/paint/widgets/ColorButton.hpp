#ifndef COLORBUTTON_HPP
# define COLORBUTTON_HPP

# include "Shape.hpp"

class ColorButton : public Element
{
    private:
        optional<Shape>         _back;

        static constexpr int    Border = 2;

    protected:
		virtual void	        onPropertiesChanged([[maybe_unused]] SDL_Renderer* renderer) override;
        virtual void	        onPositionChanged([[maybe_unused]] SDL_Renderer* renderer) override;

		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        ColorButton(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~ColorButton(void) = default;

        void                    render(SDL_Renderer* renderer);

        virtual void            onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void            onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void            onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
