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

NAME2 = viz

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c qops.c dict.c algo.c md5/md5_bitset.c md5/md5_dispatch.c \
		md5/md5_phase.c md5/md5_prmtvs.c md5/md5_rounds.c

VSRC = viz.c parse_dickens.c print_dickens.c fill.c v_parse.c normnodelink.c \
		edge_findclean.c node_findclean.c

OBJS = $(SRC:.c=.o)

VOBJS = $(VSRC:.c=.o)

LIBDIR = libft

LIB = $(LIBDIR)/libft.a

.PHONY both: $(NAME) $(NAME2)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

$(NAME2): $(VOBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME2) $(VOBJS) $(LIB)

$(LIB):
	@make -C $(LIBDIR)

.PHONY: clean fclean all re debug

debug: $(SRC) $(LIB)
	$(CC) -o debug -g $(SRC) $(LIB)

clean:
	@rm -f $(OBJS)
	@rm -f $(VOBJS)
	@make -C $(LIBDIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME2)
	@make -C $(LIBDIR) fclean

all: $(NAME) $(NAME2)

re: fclean all
