NAME = nibbler

DIR = core/

DIRLCUR = ncurses/

DIRLSFML = sfml/

DIRLSDL = sdl/

SRC = $(DIR)main.cpp\
	$(DIR)GameObject.cpp\
	Data.cpp\
	Sound.cpp\
	$(DIR)Game.cpp\
	$(DIR)Food.cpp\
	$(DIR)loader.cpp\
	$(DIR)Player.cpp\
	$(DIR)Point.cpp\
	$(DIR)Snake.cpp\
	$(DIR)Multi.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3 -Wall -Wextra -Werror -std=c++11 -I .

all: LCUR LSDL $(NAME)

LCUR:
	make -C $(DIRLCUR)

LSFML:
	make -C $(DIRLSFML)

LSDL:
	make -C $(DIRLSDL)

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

recur:
	make re -C $(DIRLCUR)

remlx:
	make re -C $(DIRLMLX)

resdl:
	make re -C $(DIRLSDL)

re: resdl recur remlx fclean all

.PHONY: clean all re fclean
