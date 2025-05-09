# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = paint-software

SRCS = srcs/main.cpp \
	srcs/Paint/Init.cpp \
	srcs/Paint/Draw.cpp \
	srcs/Paint/Paint.cpp \
	srcs/Paint/Free.cpp \
	srcs/Windows/Init.cpp \
	srcs/Windows/Free.cpp \

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -I includes/

SDLFLAG = -lSDL2

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(SDLFLAG)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)