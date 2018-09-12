/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 16:04:26 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/06 14:27:40 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTS_H
# define ANTS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

# define DICT_SIZE 4096

# define NOW 1
# define EVER 2

typedef enum	e_nodetype
{
	start,
	end,
	mid,
}				t_nodetype;	

typedef t_vec	t_nodevec;
typedef t_vec	t_linkvec;
typedef t_vec	t_npvec;
typedef t_vec	t_svec;

typedef t_node	t_npair[2];

typedef struct	s_node
{
	t_nodetype		typ;
	t_byte			visited;
	char			*name;
	t_linkvec		*links;
}				t_node;

typedef struct	s_splay
{
	struct s_splay	*pathparent;
	struct s_splay	*parent;
	struct s_splay	*left;
	struct s_splay	*right;
	t_node			*content;
	int				key;
}				t_splay;

typedef struct	s_link
{
	t_node		*node;
	int			cap;
}				t_link;

typedef struct	s_queue
{
	t_list		*start;
	t_list		*end;
}				t_queue;

typedef struct	s_path
{
	t_byte		entered_on_2;
	t_node		*current;
	t_svec		*path;
}				t_path;

char			*ft_sthreejoin(char *s1, char *s2, char *s3);

void			find_path(t_node **nodes, t_nodevec *graph, int num_ants);
t_node			*find_node(t_node **nodes, char *key);

int				index(char *s, int x);
int				dict_mod(char *op, char *key, int value);

t_queue			*q_new(t_list *list);
t_list			*q_pop(t_queue *queue);
void			q_add(t_queue *queue, t_list *list);

#endif
