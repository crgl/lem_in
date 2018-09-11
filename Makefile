# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgleason <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/06 14:09:11 by cgleason          #+#    #+#              #
#    Updated: 2018/09/06 14:17:28 by cgleason         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

CC = @gcc

CFLAGS = -Wall -Wextra -Werror -o $(NAME)

SRC = main.c splay.c

OBJS = $(SRC:.c=.o)

LIBDIR = libft

LIB = $(LIBDIR)/libft.a

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB)

$(LIB):
	@make -C $(LIBDIR)

.PHONY: clean fclean all re debug

debug: $(SRC) $(LIB)
	$(CC) -o debug -g $(SRC) $(LIB)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean

all: $(NAME)

re: fclean all
