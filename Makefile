# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 12:31:51 by rymuller          #+#    #+#              #
#    Updated: 2019/08/12 19:39:35 by mbeahan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lem-in

SRC :=	create_singly_linked_list.c \
		free_singly_linked_list.c \
		lem_in.c \
		parse_room.c \
		parse_link.c \
		queue.c

CFLAGS := -ggdb -Wall -Wextra -Werror
HEADER := -I./libft/includes
LIB := -L./libft -lft -L./ft_printf -lftprintf

all: $(NAME)

$(NAME): $(SRC)
	make -C libft
	make -C ft_printf
	gcc $(CFLAGS) $(HEADER) $(SRC) $(LIB) -o $(NAME)

clean:
	make -C libft clean
	make -C ft_printf clean

fclean:
	make -C libft fclean
	make -C ft_printf fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean flcean all re
