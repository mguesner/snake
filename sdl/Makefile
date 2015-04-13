NAME = libsdl.so

SRC = SdlData.cpp\
	init.cpp \
	  ../core/GameObject.cpp \
	  ../core/Point.cpp \
	  ../core/Snake.cpp \
	  ../core/Score.cpp \
	  ../Data.cpp \
	  SdlException.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3  -Wall -Wextra -Werror -std=c++11 -I .. -I SDL2/include -I SDL2_TFF/include

all: FREE_TYPE SDL2 SDL2_TFF $(NAME)

lib:
	make -C lib

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -dynamiclib -o $(NAME) $(OBJ) -L/Volumes/Data/nfs/zfs-student-3/users/2013/mguesner/Documents/snake/sdl/SDL2/lib -lSDL2 -lSDL2_ttf

SDL2:
	mkdir -p SDL2/junk
	curl http://www.libsdl.org/release/SDL2-2.0.3.tar.gz -o "SDL2-2.0.3.tar.gz"
	tar -xf SDL2-2.0.3.tar.gz
	( cd SDL2-2.0.3 \
	&& ./configure --prefix=$(shell pwd)/SDL2/ \
	 && $(MAKE) && $(MAKE) install )
	mv SDL2-2.0.3.tar.gz SDL2-2.0.3 SDL2/junk

FREE_TYPE:
	( cd /Volumes/Data/nfs/zfs-student-3/users/2013/mguesner/Downloads/freetype-2.5.5 3 \
		&& ./configure --prefix=$(shell pwd)/FREE_TYPE/ \
		&& $(MAKE) && $(MAKE) install)

SDL2_TFF:
	mkdir -p SDL2_TFF/junk
	curl -L https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz -o "SDL2_ttf-2.0.12.tar.gz"
	tar -xf SDL2_ttf-2.0.12.tar.gz
	( cd SDL2_ttf-2.0.12 \
	&& ./configure --prefix=$(shell pwd)/SDL2/ --with-freetype-prefix=/Volumes/Data/nfs/zfs-student-3/users/2013/mguesner/Documents/snake/sdl/FREE_TYPE --with-sdl-prefix=/Volumes/Data/nfs/zfs-student-3/users/2013/mguesner/Documents/snake/sdl/SDL2\
	&& $(MAKE) && $(MAKE) install )
	mv SDL2_ttf-2.0.12.tar.gz SDL2_ttf-2.0.12 SDL2/junk

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
