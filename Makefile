NAME = nibbler

DIR = core/

DIRLCUR = ncurses/

DIRLMLX = mlx/

SRC = $(DIR)main.cpp\
	$(DIR)GameObject.cpp\
	Data.cpp\
	$(DIR)Game.cpp\
	$(DIR)Food.cpp\
	$(DIR)loader.cpp\
	$(DIR)Player.cpp\
	$(DIR)Point.cpp\
	$(DIR)Snake.cpp\

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3 -Wall -Wextra -Werror -std=c++11 -I .

all: LCUR  $(NAME)

LCUR:
	make -C $(DIRLCUR)

LMLX:
	make -C $(DIRLMLX)

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
