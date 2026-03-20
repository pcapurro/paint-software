# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = paint-software

SRCS = srcs/main.cpp \
	srcs/paint/paintsoftware/Init.cpp \
	srcs/paint/paintsoftware/React.cpp \
	srcs/paint/paintsoftware/Routine.cpp \
	srcs/paint/paintsoftware/Exec.cpp \
	srcs/paint/paintsoftware/widgets/BrushOptions.cpp \
	srcs/paint/paintsoftware/widgets/MainBox.cpp \
	srcs/paint/paintsoftware/widgets/ToolBox.cpp \
	srcs/paint/paintframe/Init.cpp \
	srcs/paint/paintframe/Render.cpp \
	srcs/lib/base/Color.cpp \
	srcs/lib/base/Cursor.cpp \
	srcs/lib/base/Engine.cpp \
	srcs/lib/base/Font.cpp \
	srcs/lib/base/Properties.cpp \
	srcs/lib/base/ImageTexture.cpp \
	srcs/lib/base/TextTexture.cpp \
	srcs/lib/base/TTF.cpp \
	srcs/lib/element/Element.cpp \
	srcs/lib/element/Image.cpp \
	srcs/lib/element/Render.cpp \
	srcs/lib/element/Shape.cpp \
	srcs/lib/element/Text.cpp \
	srcs/lib/widgets/textfield/Cursor.cpp \
	srcs/lib/widgets/textfield/Edit.cpp \
	srcs/lib/widgets/textfield/Get.cpp \
	srcs/lib/widgets/textfield/Init.cpp \
	srcs/lib/widgets/textfield/On.cpp \
	srcs/lib/widgets/textfield/Set.cpp \
	srcs/lib/widgets/textfield/Render.cpp \
	srcs/lib/widgets/imagebutton/Init.cpp \
	srcs/lib/widgets/imagebutton/On.cpp \
	srcs/lib/widgets/imagebutton/Render.cpp \
	srcs/lib/widgets/textbutton/Get.cpp \
	srcs/lib/widgets/textbutton/Init.cpp \
	srcs/lib/widgets/textbutton/On.cpp \
	srcs/lib/widgets/textbutton/Render.cpp \
	srcs/lib/widgets/valuefield/Cursor.cpp \
	srcs/lib/widgets/valuefield/Edit.cpp \
	srcs/lib/widgets/valuefield/Get.cpp \
	srcs/lib/widgets/valuefield/Init.cpp \
	srcs/lib/widgets/valuefield/On.cpp \
	srcs/lib/widgets/valuefield/Check.cpp \
	srcs/lib/widgets/valuefield/Render.cpp \
	srcs/lib/window/dialogbox/Add.cpp \
	srcs/lib/window/dialogbox/Event.cpp \
	srcs/lib/window/dialogbox/Init.cpp \
	srcs/lib/window/dialogbox/React.cpp \
	srcs/lib/window/dialogbox/Render.cpp \
	srcs/lib/window/dialogbox/Routine.cpp \
	srcs/lib/window/dialogtextbox/Add.cpp \
	srcs/lib/window/dialogtextbox/Event.cpp \
	srcs/lib/window/dialogtextbox/Get.cpp \
	srcs/lib/window/dialogtextbox/Init.cpp \
	srcs/lib/window/dialogtextbox/React.cpp \
	srcs/lib/window/dialogtextbox/Render.cpp \
	srcs/lib/window/dialogtextbox/Routine.cpp \
	srcs/lib/window/dialogvaluesbox/Add.cpp \
	srcs/lib/window/dialogvaluesbox/Event.cpp \
	srcs/lib/window/dialogvaluesbox/Get.cpp \
	srcs/lib/window/dialogvaluesbox/Init.cpp \
	srcs/lib/window/dialogvaluesbox/React.cpp \
	srcs/lib/window/dialogvaluesbox/Render.cpp \
	srcs/lib/window/dialogvaluesbox/Routine.cpp \
	srcs/lib/window/window/Core.cpp \
	srcs/lib/window/window/Delete.cpp \
	srcs/lib/window/window/Get.cpp \
	srcs/lib/window/window/Init.cpp \
	srcs/lib/window/window/Set.cpp \

CXX = c++

CXXFLAGS = -std=c++17 \
	-I includes/ \
	-I includes/paint/ \
	-I includes/paint/widgets \
	-I includes/lib/base \
	-I includes/lib/element \
	-I includes/lib/widgets \
	-I includes/lib/window

SDLFLAGS = -lSDL2 -lSDL2_ttf

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(SDLFLAGS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
