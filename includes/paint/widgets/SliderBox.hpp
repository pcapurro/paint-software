#ifndef SLIDERBOX_HPP
# define SLIDERBOX_HPP

# include "Element.hpp"

# include "Text.hpp"
# include "Shape.hpp"

class SliderBox : public Element
{
    private:
        optional<Shape>         _background;

        optional<Text>          _title;
        optional<Text>          _valueText;

        optional<Shape>         _slider;
        optional<Shape>         _cursor;
        optional<Shape>         _sliderBox;

        const int               _minValue;
        const int               _maxValue;

        int                     _value = 0;

        void                    initTexts(const string& title, const int textSize, const string& fontPath, \
                                    const Color& textColor, SDL_Renderer* renderer);
        void                    initSlider(const Color& sliderColor);

        void                    refreshValue(const int x, const int y, SDL_Renderer* renderer);

    protected:
		virtual void	        onPropertiesChanged([[maybe_unused]] SDL_Renderer* renderer) override;
        virtual void	        onPositionChanged([[maybe_unused]] SDL_Renderer* renderer) override;

		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        SliderBox(void) = delete;

        SliderBox(const int x, const int y, const int width, const int height, const string& fontPath, \
            const int minValue, const int maxValue, const string& title, const int textSize, \
            const bool border, const int borderThickness, const Color& backColor, const Color& borderColor, \
            const Color& textColor, const Color& sliderColor, SDL_Renderer* renderer);

        ~SliderBox(void) = default;

        int                     getValue(void) const noexcept;

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

        virtual void	        onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void	        onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
