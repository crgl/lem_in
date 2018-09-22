/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 13:41:26 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/13 13:41:29 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int		is_valid_node(char *line)
{
	int	i;

	if (!ft_strchr(line, ' '))
		return (0);
	if (!ft_strchr(ft_strchr(line, ' ') + 1, ' '))
		return (0);
	i = 0;
	if (!line[0] || line[0] == 'L' || line[0] == '-')
		return (0);
	while (line[i] && line[i] != ' ')
		if (line[i++] == '-')
			return (0);
	return (1);
}

void	free_ptrmap(t_ptrmap *nodedge)
{
	int	i;

	i = 0;
	while (nodedge->names[i])
		free(nodedge->names[i++]);
	free(nodedge->states);
}

void	free_everything(t_ptrmap **nodes, t_ptrmap **edges,
			t_pmvec *doublenodes, t_pmvec *doubleedges)
{
	int	i;

	i = 0;
	while (nodes[i])
		free_ptrmap(nodes[i++]);
	i = 0;
	while (edges[i])
		free_ptrmap(edges[i++]);
	free(nodes);
	free(edges);
	vecdel(&doubleedges);
	vecdel(&doublenodes);
}

void	execute(t_ptrmap **nodes, t_ptrmap **edges, int num_ants)
{
	char		*map;
	t_ptrmap	***annotate;
	int			i;
	int			num_steps;

	map = (char *)ft_memalloc(((ROW_LEN + 1) * COLM_LEN + 1) * sizeof(char));
	annotate = (t_ptrmap ***)ft_memalloc(((ROW_LEN + 1) *
		COLM_LEN + 1) * sizeof(t_ptrmap **));
	ft_memset(map, ' ', ((ROW_LEN + 1) * COLM_LEN));
	i = 0;
	while (i < COLM_LEN)
		map[(ROW_LEN + 1) * i++ + ROW_LEN] = '\n';
	set_node_char(nodes, annotate, map, num_ants);
	i = 0;
	while (edges[i])
	{
		if (edges[i]->states == NULL)
			edges[i]->states = (bool *)ft_memalloc((num_ants +
				ft_len((void **)nodes)) * 3 * sizeof(bool));
		fill_between(map, annotate, edges[i++]);
	}
	num_steps = parse_the_dickens(nodes, edges);
	print_the_dickens(map, annotate, num_steps);
	free_maps(map, annotate);
}

int		main(void)
{
	t_ptrmap	**nodes;
	t_ptrmap	**edges;
	t_pmvec		*doublenodes;
	t_pmvec		*doubleedges;
	int			num_ants;

	doublenodes = vecnew(NULL, sizeof(t_ptrmap));
	doubleedges = vecnew(NULL, sizeof(t_ptrmap));
	nodes = NULL;
	num_ants = parse(doublenodes, doubleedges, &nodes, &edges);
	if (num_ants < 1)
	{
		ft_putendl_fd("Invalid input!", 2);
		return (-1);
	}
	execute(nodes, edges, num_ants);
	free_everything(nodes, edges, doublenodes, doubleedges);
	return (0);
}
