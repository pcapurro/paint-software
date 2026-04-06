#ifndef PAINTFRAME_HPP
# define PAINTFRAME_HPP

# include "Element.hpp"
# include "Shape.hpp"

# include "Texture.hpp"

# include "ToolBox.hpp"

class PaintFrame : public Element
{
    private:
        vector<Shape>           _pngBack;
        optional<Texture>       _paintTexture;

        vector<vector<Color>>   _paintData;

        Color                   _defaultColor;
        Color                   _pickedColor;

        int                     _selectedTool;
        int                     _brushSize;
        Color                   _selectedColor;

        std::pair<int, int>     _lineStart = { -1, -1 };
        std::pair<int, int>     _lineEnd = { -1, -1 };

        std::pair<int, int>     _rectStart = { -1, -1 };
        std::pair<int, int>     _rectEnd = { -1, -1 };

		static constexpr int	PngWidth = 30;
		static constexpr int	PngHeight = 30;

        void                    initPngBack(void);

        void                    initPaintData(void);
        void                    initPaintTexture(SDL_Renderer* renderer);

        void                    paintBrush(const int x, const int y);
        void                    paintPencil(const int x, const int y);

        void                    paintBucket(const int x, const int y);
        void                    paintSpray(const int x, const int y);

        void                    erase(const int x, const int y);
        void                    pick(const int x, const int y);

        void                    paintRectangle(const int endX, const int endY);
        void                    paintLine(const int endX, const int endY);

        void                    updateTexture(void);

    public:
        PaintFrame(const int x, const int y, const int width, \
            const int height, Color& defaultColor, const int selectedTool, \
            const int brushSize, const Color& selectedColor, SDL_Renderer* renderer);

        ~PaintFrame(void) = default;

        void                    render(SDL_Renderer* renderer);

        void                    clear(void);

        Color                   getPickedColor(void) const noexcept;

        void                    setSelectedTool(const int tool);
        void                    setBrushSize(const int newBrushSize);
        void                    setSelectedColor(const Color& newColor);

        virtual void            onMouseDown([[maybe_unused]] const bool held = false, \
            [[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void            onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void            onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void            onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
