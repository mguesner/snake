NAME = nibbler

DIR = core/

NAME1 = libcurses.so

DIR1 = ncurses/

SRC = $(DIR)main.cpp\
	$(DIR)GameObject.cpp\
	$(DIR)Game.cpp\
	$(DIR)Food.cpp\
	$(DIR)loader.cpp\
	$(DIR)Player.cpp\
	$(DIR)Point.cpp\
	$(DIR)Snake.cpp\

SRC1 = $(DIR1)NCursesData.cpp\
	$(DIR1)init.cpp \
	$(DIR1)Menu.cpp\
	$(DIR)GameObject.cpp\
	$(DIR)Point.cpp\

OBJ = $(SRC:.cpp=.o)

OBJ1 = $(SRC1:.cpp=.o)

CC = clang++ -g -O3 -Wall -Wextra -Werror -std=c++11 -I .

all: $(NAME) $(NAME1)

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

$(NAME1): $(OBJ1)
	$(CC) -dynamiclib -o $(NAME1) $(OBJ1) -lncurses

clean:
	rm -f $(OBJ)
	rm -f $(OBJ1)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME1)

re: fclean all

.PHONY: clean all re fclean
