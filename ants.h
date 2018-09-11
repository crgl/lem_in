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

typedef enum	e_nodetype
{
	start,
	end,
	mid,
}				t_nodetype;	

typedef t_vec	t_nodevec;
typedef t_vec	t_linkvec;

typedef struct	s_node
{
	t_nodetype		typ;
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

typedef struct	s_linkcut
{
}				t_linkcut;

void			find_path(t_node **nodes, t_nodevec *graph);

#endif
