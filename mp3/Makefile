NAME = sound.so

SRC = Sound.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3  -Wall -Wextra -Werror -std=c++11

all: $(NAME)

lib:
	make -C lib

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -dynamiclib -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
