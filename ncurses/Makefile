NAME = libcurses.so

SRC = NCursesData.cpp\
	init.cpp \
	  ../core/GameObject.cpp \
	  ../core/Point.cpp \
	  ../core/Snake.cpp \
	  ../core/Score.cpp \
	  ../Data.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3 -Wall -Wextra -Werror -std=c++11 -I ..

all: $(NAME)

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -dynamiclib -o $(NAME) $(OBJ) -lncurses

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
