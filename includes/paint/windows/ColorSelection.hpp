#ifndef COLORSELECTION_HPP
# define COLORSELECTION_HPP

# include "Window.hpp"

# include "Text.hpp"
# include "Shape.hpp"
# include "Image.hpp"

# include "TextButton.hpp"
# include "ValueField.hpp"

# include "ColorButton.hpp"

class ColorSelection : public Window
{
	private:
		vector<unique_ptr<Element>>		_elements;

		unique_ptr<Element>				_okButton;

		unique_ptr<ValueField>			_leftUpField;
		unique_ptr<Text>				_leftUpError;

		unique_ptr<ValueField>			_leftDownField;
		unique_ptr<Text>				_leftDownError;

		unique_ptr<ValueField>			_rightUpField;
		unique_ptr<Text>				_rightUpError;

		unique_ptr<ValueField>			_rightDownField;
		unique_ptr<Text>				_rightDownError;

		optional<ColorButton>			_colorView;

		size_t							_tabCursor = 4;

		string							_fontPath;

		bool							_error = false;
		vector<uint8_t>					_finalValues;


		static constexpr int			limitHeight = 1;

		static constexpr int			CenterSpaceWidth = 20;
		static constexpr int			CenterSpaceHeight = 20;

		static constexpr int			ColorViewWidth = 50;

		void							addLogo(const int cursorX, const int cursorY, const string& logoPath, \
											const int logoWidth, const int logoHeight, const bool centered = false);

		void							addTitleText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);
		void							addTitleLimit(const int cursorX, const int cursorY, const int width);

		void							addText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);

		void							addLeftFieldsTitles(const string& fontPath);
		void							addLeftFields(const string& fontPath, const int maxText);
		void							addLeftFieldsErrors(const string& fontPath);

		void							addRightFieldsTitles(const string& fontPath);
		void							addRightFields(const string& fontPath, const int maxText);
		void							addRightFieldsErrors(const string& fontPath);

		void							addColorView(void);

		void							addButton(const string& fontPath);

	public:
		ColorSelection(void) = delete;
		ColorSelection(const string& name, const string& fontPath, const int width = 400, \
			const int height = 170, const int displayMode = Window::LightMode, const string& titleText = "[Title]", \
			const bool titleLimit = false, const string& text = "[Text]");

		~ColorSelection(void) = default;
		
		virtual void					render(void);

		void							reactError(void);

		void 							reactMouseMotion(const int x, const int y);
		int								reactMouseButtonUp(const int x, const int y);
		void 							reactMouseButtonDown(const int x, const int y, const int clicks);

		int								reactKeyButtonDown(const int key);
		void 							reactCharactersDown(const char* text);

		void							reactColorUpdate(void);

		virtual int						reactEvent(SDL_Event* event);

        vector<uint8_t>					getFinalValues(void);
};

#endif
