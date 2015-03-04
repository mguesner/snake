NAME = nibbler

DIR = core/

DIRLCUR = ncurses/

SRC = $(DIR)main.cpp\
	$(DIR)GameObject.cpp\
	$(DIR)Game.cpp\
	$(DIR)Food.cpp\
	$(DIR)loader.cpp\
	$(DIR)Player.cpp\
	$(DIR)Point.cpp\
	$(DIR)Snake.cpp\

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3 -Wall -Wextra -Werror -std=c++11 -I .

all: LCUR $(NAME)

LCUR:
	make -C $(DIRLCUR)

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
