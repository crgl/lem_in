/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 13:22:20 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/15 13:22:26 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	free_graph(t_nodevec *graph)
{
	t_node			*loc;
	unsigned long	i;

	loc = (t_node *)graph->e;
	i = 0;
	while (i < graph->len / sizeof(t_node))
	{
		free(loc[i].name);
		vecdel(&(loc[i].links));
		i++;
	}
	vecdel(&graph);
}

void	free_and_clear(t_nodevec *graph)
{
	free_graph(graph);
	dict_mod("clear", NULL, 0);
	ft_putendl("ERROR");
	exit(-1);
}

int		node_cmp(void *n1, void *n2)
{
	return (ft_strcmp(((t_node *)n1)->name, ((t_node *)n2)->name));
}

int		is_valid_node(char *line)
{
	int	i;

	if (!ft_strchr(line, ' '))
		return (0);
	if (!ft_strchr(ft_strchr(line, ' ') + 1, ' '))
		return (0);
	*ft_strchr(line, ' ') = '\0';
	i = 0;
	if (!line[0] || line[0] == 'L' || line[0] == '-')
		return (0);
	while (line[++i])
		if (line[i] == '-')
			return (0);
	return (1);
}

t_node	*find_node(t_node **nodes, char *key)
{
	int	i;
	int	upper;
	int	lower;

	i = ft_len((void **)nodes) / 2;
	upper = ft_len((void **)nodes) - 1;
	lower = 0;
	while (upper != lower)
	{
		if (ft_strequ(key, nodes[i]->name))
			return (nodes[i]);
		if (ft_strcmp(key, nodes[i]->name) < 0)
		{
			upper = i;
			i = (i + lower - 1) / 2;
		}
		else
		{
			lower = i;
			i = (i + upper + 1) / 2;
		}
	}
	if (ft_strequ(key, nodes[i]->name))
		return (nodes[i]);
	return (NULL);
}
