NAME = libmlx.so

SRC = MLXData.cpp\
	windows.cpp\
	init.cpp \
	  ../core/GameObject.cpp \
	  ../core/Point.cpp \
	  ../core/Snake.cpp \
	  ../Data.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3  -Wall -Wextra -Werror -std=c++11 -I ..

all: lib $(NAME)

lib:
	make -C lib

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -dynamiclib -o $(NAME) $(OBJ) -framework OpenGL -framework AppKit lib/lib.a libmlx.a

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
