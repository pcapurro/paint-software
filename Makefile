# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = paint-software

SRCS = srcs/main.cpp \
	srcs/paint/windows/paintsoftware/Init.cpp \
	srcs/paint/windows/paintsoftware/React.cpp \
	srcs/paint/windows/paintsoftware/Render.cpp \
	srcs/paint/windows/paintsoftware/Exec.cpp \
	srcs/paint/windows/paintsoftware/Update.cpp \
	srcs/paint/windows/paintsoftware/Tools.cpp \
	srcs/paint/windows/colorselection/Add.cpp \
	srcs/paint/windows/colorselection/LeftAdd.cpp \
	srcs/paint/windows/colorselection/RightAdd.cpp \
	srcs/paint/windows/colorselection/Get.cpp \
	srcs/paint/windows/colorselection/Init.cpp \
	srcs/paint/windows/colorselection/React.cpp \
	srcs/paint/windows/colorselection/Render.cpp \
	srcs/paint/windows/PathSelection.cpp \
	srcs/paint/widgets/ColorButton.cpp \
	srcs/paint/widgets/MainBox.cpp \
	srcs/paint/widgets/SliderBox.cpp \
	srcs/paint/widgets/ToolBox.cpp \
	srcs/paint/widgets/PaintFrame.cpp \
	srcs/paint/softwares/Paint.cpp \
	srcs/paint/softwares/PaintingSize.cpp \
	srcs/paint/softwares/ProjectName.cpp \
	srcs/lib/bases/Color.cpp \
	srcs/lib/bases/Cursor.cpp \
	srcs/lib/bases/Engine.cpp \
	srcs/lib/bases/Font.cpp \
	srcs/lib/bases/Properties.cpp \
	srcs/lib/bases/ImageTexture.cpp \
	srcs/lib/bases/TextTexture.cpp \
	srcs/lib/bases/TTF.cpp \
	srcs/lib/elements/Element.cpp \
	srcs/lib/elements/Image.cpp \
	srcs/lib/elements/Render.cpp \
	srcs/lib/elements/Shape.cpp \
	srcs/lib/elements/Text.cpp \
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
	srcs/lib/windows/dialogbox/Add.cpp \
	srcs/lib/windows/dialogbox/Init.cpp \
	srcs/lib/windows/dialogbox/React.cpp \
	srcs/lib/windows/dialogbox/Render.cpp \
	srcs/lib/windows/dialogtextbox/Add.cpp \
	srcs/lib/windows/dialogtextbox/Get.cpp \
	srcs/lib/windows/dialogtextbox/Init.cpp \
	srcs/lib/windows/dialogtextbox/React.cpp \
	srcs/lib/windows/dialogtextbox/Render.cpp \
	srcs/lib/windows/dialogvaluesbox/Add.cpp \
	srcs/lib/windows/dialogvaluesbox/Get.cpp \
	srcs/lib/windows/dialogvaluesbox/Init.cpp \
	srcs/lib/windows/dialogvaluesbox/React.cpp \
	srcs/lib/windows/dialogvaluesbox/Render.cpp \
	srcs/lib/windows/window/Core.cpp \
	srcs/lib/windows/window/Delete.cpp \
	srcs/lib/windows/window/Get.cpp \
	srcs/lib/windows/window/Init.cpp \
	srcs/lib/windows/window/Set.cpp \
	srcs/lib/softwares/DialogBoxPreview.cpp \
	srcs/lib/softwares/DialogTextBoxPreview.cpp \
	srcs/lib/softwares/DialogValuesBoxPreview.cpp \

CXX = c++

CXXFLAGS = -std=c++17 \
	-I includes/ \
	-I includes/paint/ \
	-I includes/paint/widgets \
	-I includes/paint/windows \
	-I includes/paint/softwares \
	-I includes/lib/bases \
	-I includes/lib/elements \
	-I includes/lib/widgets \
	-I includes/lib/windows \
	-I includes/lib/softwares

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
