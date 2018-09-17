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

# define IS_MID(node) ((node)->typ == mid)
# define OFF_PATH(node) (((node)->visited & EVER) == 0)
# define UNSEARCHED(node) (((node)->visited & NOW) == 0)
# define UNRESTRICTED(path) (OFF_PATH((path)->current) || (path)->entered_on_2)
# define AVAIL(node) (IS_MID(node) && UNSEARCHED(node))

# define MARKS_START(line) ft_strequ(line + 2, "start")
# define MARKS_END(line) ft_strequ(line + 2, "end")
# define START_OR_END(line) (ft_strequ(line + 2, "start") ? start : end)

# define REV(link) (dict_mod("get", link, 0) == 2)

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

typedef struct	s_node
{
	t_nodetype		typ;
	t_byte			visited;
	char			*name;
	t_linkvec		*links;
}				t_node;

typedef t_node	*t_npair[2];

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

void			find_path(t_node **nodes, int num_ants);
t_node			*find_node(t_node **nodes, char *key);

int				index_of(char *s, int x);
int				dict_mod(char *op, char *key, int value);

t_queue			*q_new(t_list *list);
t_list			*q_pop(t_queue *queue);
void			q_add(t_queue *queue, t_list *list);

void			free_graph(t_nodevec *graph);
void			free_and_clear(t_nodevec *graph);
int				node_cmp(void *n1, void *n2);
int				is_valid_node(char *line);
t_node			*find_node(t_node **nodes, char *key);

void			add_link(t_nodevec *graph, t_node **nodes, char *line);
void			add_node(t_nodevec *graph, char *line, t_nodetype typ);
int				add_special(int fd, t_nodevec *graph, char **line);
char			*add_all_nodes(int fd, t_nodevec *graph, char *line);

void			search_and_destroy(t_queue *to_search, t_path *found,
					t_svec *to_free);
void			print_and_free(t_queue *rows);
void			send_out(t_npvec *sequence, int num_ants, t_list *oldrow,
					t_list *row);
void			paths_from_start(t_node **nodes, int start_ind,
					t_npvec *sequence);

char			*inspect_link(t_node **nodes, t_queue *to_search,
					t_path *found, t_node *to_inspect);
t_path			*get_current_path(t_queue *to_search, t_svec **to_free);
int				find_flow(t_queue *to_search, t_node **nodes, size_t i);
void			traverse(char *link, t_node **nodes);
void			add_node_to_queue(char *new_link, t_path *found,
					t_node *to_inspect, t_queue *to_search);
t_list			*make_list_of(t_npair just_traveled);

#endif
