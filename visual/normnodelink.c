/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normnodelink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:46:42 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/15 12:46:45 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	add_node(t_pmvec *doublenodes, char *line,
			t_color inactive, t_color active)
{
	t_ptrmap	*the_stuff;

	if (is_valid_node(line))
	{
		the_stuff = (t_ptrmap *)ft_memalloc(sizeof(t_ptrmap));
		the_stuff->active = active;
		the_stuff->inactive = inactive;
		the_stuff->coords[0][0] = ft_atoi(ft_strchr(line, ' '));
		the_stuff->coords[0][1] = ft_atoi(ft_strrchr(line, ' '));
		*ft_strchr(line, ' ') = '\0';
		the_stuff->names[0] = ft_strdup(line);
		veccat(doublenodes, the_stuff, sizeof(t_ptrmap));
		free(the_stuff);
	}
	else
	{
		ft_printf("ERROR: Invalid node\n");
		exit(-1);
	}
}

void	flip_node(char **node2, char **line)
{
	char *tmp;

	if (ft_strcmp(*node2, *line) < 0)
	{
		tmp = *line;
		*line = *node2;
		*node2 = tmp;
	}
}

void	add_link(t_ptrmap **nodes, t_pmvec *doubleedges, char *line)
{
	t_ptrmap	*the_stuff;
	char		*node2;

	node2 = ft_strchr(line, '-') + 1;
	*ft_strchr(line, '-') = '\0';
	if (!find_node(nodes, line) || !find_node(nodes, node2))
	{
		ft_printf("ERROR: Invalid link!\n");
		exit(-1);
	}
	the_stuff = (t_ptrmap *)ft_memalloc(sizeof(t_ptrmap));
	the_stuff->active = E_ACT;
	the_stuff->inactive = E_INACT;
	flip_node(&node2, &line);
	the_stuff->coords[0][0] = find_node(nodes, line)->coords[0][0];
	the_stuff->coords[0][1] = find_node(nodes, line)->coords[0][1];
	the_stuff->coords[1][0] = find_node(nodes, node2)->coords[0][0];
	the_stuff->coords[1][1] = find_node(nodes, node2)->coords[0][1];
	the_stuff->names[0] = ft_strdup(line);
	the_stuff->names[1] = ft_strdup(node2);
	veccat(doubleedges, the_stuff, sizeof(t_ptrmap));
	free(the_stuff);
}

void	set_norm_coords(t_ptrmap **nodes, int set[4])
{
	int i;

	i = 0;
	while ((nodes[i]) != NULL)
	{
		nodes[i]->coords[0][0] = (nodes[i]->coords[0][0] -
			(LL)set[0]) * (LL)199 / set[1];
		nodes[i]->coords[0][1] = (nodes[i]->coords[0][1] -
			(LL)set[2]) * (LL)49 / set[3];
		i++;
	}
}

void	normalize(t_ptrmap **nodes)
{
	int set[4];
	int i;

	i = 0;
	set[0] = INT_MAX;
	set[1] = INT_MIN;
	set[2] = INT_MAX;
	set[3] = INT_MIN;
	while ((nodes[i]) != NULL)
	{
		if (nodes[i]->coords[0][0] > set[1])
			set[1] = nodes[i]->coords[0][0];
		if (nodes[i]->coords[0][0] < set[0])
			set[0] = nodes[i]->coords[0][0];
		if (nodes[i]->coords[0][1] > set[3])
			set[3] = nodes[i]->coords[0][1];
		if (nodes[i]->coords[0][1] < set[2])
			set[2] = nodes[i]->coords[0][1];
		i++;
	}
	set_norm_coords(nodes, set);
}
