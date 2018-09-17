/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 21:48:20 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/13 21:48:26 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdbool.h>
# include <limits.h>
# include "../libft/libft.h"

# define ROW_LEN 200
# define COLM_LEN 50
# define E_INACT 0x003d0099
# define E_ACT 0x00e0ccff
# define SN_INACT 0x0000997a
# define SN_ACT 0x0000ffcb
# define MN_INACT 0x00005999
# define MN_ACT 0x00f7fcf7
# define EN_INACT 0x007c0101
# define EN_ACT 0x00ff0000
# define LL long long

typedef unsigned int	t_color;
typedef int				t_pair[2];
typedef t_vec			t_svec;

typedef struct			s_ptrmap
{
	t_color			inactive;
	t_color			active;
	t_pair			coords[3];
	char			*names[3];
	bool			*states;
}						t_ptrmap;

typedef t_vec			t_pmvec;

t_ptrmap				*find_node(t_ptrmap **nodes, char *key);
void					print_the_dickens(char *map, t_ptrmap ***annotate,
							int num_steps);
int						parse_the_dickens(t_ptrmap **nodes, t_ptrmap **edges);
t_ptrmap				*find_edge(t_ptrmap **edges, char *key1, char *key2);
void					fill_between(char *map, t_ptrmap ***annotate,
							t_ptrmap *edge);
void					add_to_annotation(t_ptrmap ***annotate,
							t_ptrmap *nodedge, int ind);
int						parse(t_pmvec *doublenodes, t_pmvec *doubleedges,
							t_ptrmap ***nodes, t_ptrmap ***edges);
t_ptrmap				**clean_up(t_pmvec *doublenodes);
t_ptrmap				**edge_clean(t_pmvec *doubleedges);

void					add_node(t_pmvec *doublenodes, char *line,
							unsigned int inactive, unsigned int active);
void					add_link(t_ptrmap **nodes, t_pmvec *doubleedges,
							char *line);
void					normalize(t_ptrmap **nodes);
int						is_valid_node(char *line);

void					set_node_char(t_ptrmap **nodes, t_ptrmap ***annotate,
							char *map, int num_ants);

void					free_maps(char *map, t_ptrmap ***annotate);

#endif
