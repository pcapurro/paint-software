#ifndef MAINBOX_HPP
# define MAINBOX_HPP

# include "Element.hpp"
# include "ImageButton.hpp"

class MainBox : public Element
{
    private:
        vector<unique_ptr<ImageButton>>     _buttons;

        int                                 _lastButtonClicked = NONE;

        void            initButtons(SDL_Renderer* renderer);

    public:
        MainBox(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~MainBox(void) = default;

        int             getLastButtonClicked(void);

        void            render(SDL_Renderer* renderer);

        virtual void    onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void    onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void    onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void    onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
