#ifndef MAINBOX_HPP
# define MAINBOX_HPP

# include "Element.hpp"
# include "ImageButton.hpp"

class MainBox : public Element
{
    private:
        vector<unique_ptr<ImageButton>>     _buttons;

    public:
        MainBox(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~MainBox(void) = default;

        void        render(SDL_Renderer* renderer);
};

#endif
