NAME = nibbler

DIR = core/

DIRLCUR = ncurses/

DIRLSFML = sfml/

DIRLSDL = sdl/

DIRSOUND = mp3/

SRC = $(DIR)main.cpp\
	$(DIR)GameObject.cpp\
	Data.cpp\
	$(DIR)Game.cpp\
	$(DIR)Food.cpp\
	$(DIR)loader.cpp\
	$(DIR)Player.cpp\
	$(DIR)Point.cpp\
	$(DIR)Snake.cpp\
	$(DIR)Multi.cpp\
	$(DIR)Score.cpp\
	$(DIR)DataEx.cpp\
	$(DIR)Serializer.cpp\
	$(DIR)PowerUp.cpp\
	$(DIR)Obstacle.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3 -Wall -Wextra -Werror -std=c++11 -I .

all: LCUR LSDL LSFML LSOUND $(NAME)

LCUR:
	make -C $(DIRLCUR)

LSOUND:
	make -C $(DIRSOUND)

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

resfml:
	make re -C $(DIRLSFML)

resdl:
	make re -C $(DIRLSDL)
resound:
	make re -C $(DIRSOUND)

re: resdl recur resound resfml fclean all

.PHONY: clean all re fclean
