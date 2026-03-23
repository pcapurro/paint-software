#ifndef MACROS_HPP
# define MACROS_HPP

/* UI config */

# define MIN_WINDOW_W 300
# define MIN_WINDOW_H 60

# define MAX_BUTTONS 4

# define HIGHLIGHT_OPACITY 100
# define FOCUS_OPACITY 200

# define CURSOR_WIDTH 1
# define DEF_SELECT_COLOR BLUE

/* DialogBox paramaters */

# define DARK_MODE 1
# define LIGHT_MODE 0

/* State */

# define NONE 0
# define OK 42
# define END 84
# define RETURN 168

/* Render values */

# define BORDER_SELECT 21
# define CORNER_SELECT 22
# define CENTER_SELECT 23
# define CENTER_SELECT_X 24
# define HIGHLIGHT_SELECT 25

/* UI Ratios */

# define TITLE_RATIO 0.10f
# define TEXT_RATIO 0.08f

# define LIMIT_RATIO 0.05f
# define LIMIT_HEIGHT 1

/* UI Colors */

# define WHITE {255, 255, 255, 255}
# define BLACK {0, 0, 0, 255}

# define RED {255, 0, 0, 255}
# define GREEN {0, 255, 0, 255}
# define BLUE {0, 0, 255, 255}
# define YELLOW {255, 255, 0, 255}

# define INVISIBLE {0, 0, 0, 0}

/* Text colors */

# define RED_TXT "\033[31m"
# define GREEN_TXT "\033[32m"
# define GREY_TXT "\033[90m"

# define END_COLOR "\033[0m"

/* Default dimensions */

# define DEF_LEFT_W 190
# define DEF_RIGHT_W 30

# define DEF_UP_H 30
# define DEF_DOWN_H 30

# define DEF_MAX_PAINT_W 1280
# define DEF_MAX_PAINT_H 720

# define DEF_MIN_W DEF_MAX_PAINT_W
# define DEF_MIN_H DEF_MAX_PAINT_H

# define DEF_BUTTON_W 65
# define DEF_BUTTON_H 65

# define CENTER_SPACE_W 20
# define CENTER_SPACE_H 20

# define LEFT_PANELS_W 150

# define DEF_MAIN_H 130
# define DEF_TOOLBOX_H 260

# define DEF_BRUSH_FIELD_H 20

# define DEF_SLIDEBOX_H 45

# define DEF_SLIDER_H 3
# define SLIDER_CURSOR_W 6
# define SLIDER_CURSOR_H 6

# define DEF_MAIN_COLOR_H 45
# define DEF_SIDE_COLOR_H 36

# define BORDER 2

/* Limits */

# define W_LIMIT 20

# define H_UP_LIMIT 30
# define H_DOWN_LIMIT 30

/* Default colors */

# define DEF_BACK_COLOR {42, 42, 42, 255}
# define DEF_TOOL_SELECT_COLOR {25, 200, 50, 130}

/* Main buttons */

# define SAVE 1
# define CANCEL 2
# define BACK 3
# define FORWARD 4

/* Tools */

# define BRUSH 1
# define PENCIL 2

# define BUCKET 3
# define SPRAY 4

# define ERASER 5
# define PICKER 6

# define LINE 7
# define TEXT 8

/* Brush options */

# define BRUSH_SIZE_MIN 1
# define BRUSH_SIZE_MAX 50

# define BRUSH_DEF_SIZE 21

# define OPACITY_MIN 1
# define OPACITY_MAX 255

# define OPACITY_DEF 255

/* Color selection */

# define COLOR_VIEW_W 50

#endif
