#ifndef TOOLBOX_HPP
# define TOOLBOX_HPP

# include "Element.hpp"
# include "ImageButton.hpp"
# include "Cursor.hpp"

class ToolBox : public Element
{
    private:
        vector<unique_ptr<ImageButton>>     _buttons;
        int                                 _selectedTool = Brush;

        static constexpr int                Border = 2;

        static constexpr int                CenterSpaceWidth = 20;
		static constexpr int                CenterSpaceHeight = 20;

        static constexpr int	            ButtonWidth = 65;
		static constexpr int	            ButtonHeight = 65;

        void                                initButtons(SDL_Renderer* renderer);

    public:
        ToolBox(const int x, const int y, const int width, const int height, \
            const Color& writeColor, SDL_Renderer* renderer);

        ~ToolBox(void) = default;

        int                                 getSelectedTool(void) const noexcept;
        static string                       getToolPath(const int tool);

        void                                render(SDL_Renderer* renderer);

        virtual void                        onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void                        onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void                        onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void                        onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

        static constexpr int                Brush = 1;
		static constexpr int                Pencil = 2;

		static constexpr int                Bucket = 3;
		static constexpr int                Spray = 4;

		static constexpr int                Eraser = 5;
		static constexpr int                Picker = 6;

		static constexpr int                Line = 7;
		static constexpr int                Rectangle = 8;
};

#endif
