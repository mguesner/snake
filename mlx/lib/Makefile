# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nguezell <nguezell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/24 09:21:09 by nguezell          #+#    #+#              #
#    Updated: 2015/01/21 17:16:02 by nguezell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lib.a
SRC = ft_easylibx.c\
	fuckthenorm.c

OBJ = $(SRC:.c=.o)
FLAG = -Wextra -Werror -Wall
CC = gcc -g $(FLAG)

all: $(NAME)
$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: clean all re fclean
