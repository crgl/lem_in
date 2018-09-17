/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 11:26:38 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/15 11:26:51 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	add_to_annotation(t_ptrmap ***annotate, t_ptrmap *nodedge, int ind)
{
	int			len;
	t_ptrmap	**tmp;
	int			i;

	if (annotate[ind] == NULL)
	{
		annotate[ind] = (t_ptrmap **)ft_memalloc(sizeof(t_ptrmap *) * 2);
		annotate[ind][0] = nodedge;
	}
	else
	{
		len = ft_len((void **)annotate[ind]);
		tmp = (t_ptrmap **)ft_memalloc(sizeof(t_ptrmap *) * (len + 2));
		i = 0;
		while (i < len)
		{
			tmp[i] = annotate[ind][i];
			i++;
		}
		tmp[len] = nodedge;
		free(annotate[ind]);
		annotate[ind] = tmp;
	}
}

void	x_shift(int x_start, char *map, t_ptrmap ***annotate, t_ptrmap *edge)
{
	while (x_start < edge->coords[1][0])
	{
		if (map[x_start + edge->coords[0][1] * (ROW_LEN + 1)] == ' ')
			map[x_start + edge->coords[0][1] * (ROW_LEN + 1)] = '>';
		if (map[x_start + edge->coords[0][1] * (ROW_LEN + 1)] != '@')
			add_to_annotation(annotate, edge,
				x_start + edge->coords[0][1] * (ROW_LEN + 1));
		x_start++;
	}
	while (x_start > edge->coords[1][0])
	{
		if (map[x_start + edge->coords[0][1] * (ROW_LEN + 1)] == ' ')
			map[x_start + edge->coords[0][1] * (ROW_LEN + 1)] = '>';
		if (map[x_start + edge->coords[0][1] * (ROW_LEN + 1)] != '@')
			add_to_annotation(annotate, edge,
				x_start + edge->coords[0][1] * (ROW_LEN + 1));
		x_start--;
	}
}

void	y_shift(int y_start, char *map, t_ptrmap ***annotate, t_ptrmap *edge)
{
	while (y_start < edge->coords[1][1])
	{
		if (map[edge->coords[1][0] + y_start * (ROW_LEN + 1)] == ' ')
			map[edge->coords[1][0] + y_start * (ROW_LEN + 1)] = 'X';
		if (map[edge->coords[1][0] + y_start * (ROW_LEN + 1)] != '@')
			add_to_annotation(annotate, edge,
				edge->coords[1][0] + y_start * (ROW_LEN + 1));
		y_start++;
	}
	while (y_start > edge->coords[1][1])
	{
		if (map[edge->coords[1][0] + y_start * (ROW_LEN + 1)] == ' ')
			map[edge->coords[1][0] + y_start * (ROW_LEN + 1)] = 'X';
		if (map[edge->coords[1][0] + y_start * (ROW_LEN + 1)] != '@')
			add_to_annotation(annotate, edge,
				edge->coords[1][0] + y_start * (ROW_LEN + 1));
		y_start--;
	}
}

void	fill_between(char *map, t_ptrmap ***annotate, t_ptrmap *edge)
{
	int x_start;
	int y_start;

	x_start = edge->coords[0][0];
	y_start = edge->coords[0][1];
	x_shift(x_start, map, annotate, edge);
	y_shift(y_start, map, annotate, edge);
}

void	set_node_char(t_ptrmap **nodes, t_ptrmap ***annotate,
			char *map, int num_ants)
{
	int i;

	i = 0;
	while (nodes[i])
	{
		if (nodes[i]->states == NULL)
			nodes[i]->states = (bool *)ft_memalloc((num_ants +
				ft_len((void **)nodes)) * 3 * sizeof(bool));
		if (map[nodes[i]->coords[0][0] + nodes[i]->coords[0][1] *
			(ROW_LEN + 1)] == ' ')
			map[nodes[i]->coords[0][0] + nodes[i]->coords[0][1] *
			(ROW_LEN + 1)] = '@';
		add_to_annotation(annotate, nodes[i], nodes[i]->coords[0][0] +
			nodes[i]->coords[0][1] * (ROW_LEN + 1));
		i++;
	}
}
