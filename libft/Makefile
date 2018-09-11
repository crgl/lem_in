# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgleason <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/09 11:26:27 by cgleason          #+#    #+#              #
#    Updated: 2018/08/15 16:02:46 by cgleason         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

SRC = mem1.c mem2.c ft_strlen.c copycat.c strfind.c strcomp.c \
	  ft_atoi.c numtoa.c char_checks.c casemod.c \
	  strlife.c striter_over.c strfresh.c ft_strsplit.c \
	  put_stuff.c put_stuff_fd.c \
	  lstlife.c lstiter_over.c \
	  vecs.c vec_heap.c \
	  get_next_line.c \
	  wstrmod.c wchar_utf8.c

DIRPF = printf

PFSRC = $(DIRPF)/ft_printf.c $(DIRPF)/nine11.c $(DIRPF)/number_printing.c \
		$(DIRPF)/string_printing.c $(DIRPF)/misc_printing.c \
		$(DIRPF)/num_help.c $(DIRPF)/fluffers.c $(DIRPF)/color_mod.c

PFOBJS = $(PFSRC:.c=.o)

OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS) $(PFOBJS) libft.h $(DIRPF)/printf.h
	@ar -rc libft.a $(OBJS) $(PFOBJS)
	@ranlib libft.a

.PHONY: clean fclean all re

clean:
	@rm -f $(OBJS) $(PFOBJS)

fclean: clean
	@rm -f $(NAME)

all: $(NAME)

re: fclean all
