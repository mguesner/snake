NAME = nibbler

NAME1 = libcurses.so

SRC = main.cpp\

SRC1 = NCursesData.cpp\
	init.cpp

OBJ = $(SRC:.cpp=.o)

OBJ1 = $(SRC1:.cpp=.o)

CC = clang++ -g -O3 -Wall -Wextra -Werror -std=c++11

all: $(NAME) $(NAME1)

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

$(NAME1): $(OBJ1)
	$(CC) -dynamiclib -o $(NAME1) $(OBJ1)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
