# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = paint-software

SRCS = srcs/main.cpp \
	srcs/Paint.cpp \
	srcs/Windows/Window.cpp \
	srcs/Windows/Software.cpp \
	srcs/Windows/YesNo.cpp \
	srcs/Windows/OkCancel.cpp \
	srcs/Windows/Ok.cpp \
	srcs/Tools/Element.cpp \
	srcs/Tools/Texture.cpp \
	srcs/Tools/Tools.cpp \

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -I includes/ -I includes/Tools -I includes/Windows

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