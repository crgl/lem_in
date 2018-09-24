# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgleason <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/06 14:09:11 by cgleason          #+#    #+#              #
#    Updated: 2018/09/15 18:40:12 by cgleason         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

NAME2 = viz

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

SRC = algo/main.c algo/qops.c algo/dict.c algo/algo.c \
		algo/flow.c algo/free_print.c algo/helpers.c algo/adders.c \
		md5/md5_bitset.c md5/md5_dispatch.c \
		md5/md5_phase.c md5/md5_prmtvs.c md5/md5_rounds.c \

VSRC = visual/viz.c visual/parse_dickens.c visual/print_dickens.c \
		visual/fill.c visual/v_parse.c visual/normnodelink.c \
		visual/edge_findclean.c visual/node_findclean.c \

OBJS = $(SRC:.c=.o)

VOBJS = $(VSRC:.c=.o)

LIBDIR = libft

LIB = $(LIBDIR)/libft.a

both: $(NAME) $(NAME2)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

$(NAME2): $(VOBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME2) $(VOBJS) $(LIB)

$(LIB):
	@make -C $(LIBDIR)

.PHONY: clean fclean all re debug both

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
