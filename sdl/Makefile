NAME = libsdl.so

SRC = MLXData.cpp\
	windows.cpp\
	init.cpp \
	  ../core/GameObject.cpp \
	  ../core/Point.cpp \
	  ../core/Snake.cpp \
	  ../Data.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3  -Wall -Wextra -Werror -std=c++11 -I ..

all: SDL2

lib:
	make -C lib

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -dynamiclib -o $(NAME) $(OBJ) -framework OpenGL -framework AppKit lib/lib.a minilibx_macos/libmlx.a

SDL2:
	mkdir -p SDL2/junk
	curl http://www.libsdl.org/release/SDL2-2.0.3.tar.gz -o "SDL2-2.0.3.tar.gz"
	tar xf SDL2-2.0.3.tar.gz
	( cd SDL2-2.0.3 \
	&& ./configure --prefix=$(shell pwd)/SDL2/ \
	 && $(MAKE) && $(MAKE) install )
	mv SDL2-2.0.3.tar.gz SDL2-2.0.3 SDL2/junk

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
