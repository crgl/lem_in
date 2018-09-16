/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:17:42 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/06 14:23:21 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

t_node	**clean_up(t_nodevec *graph)
{
	t_node	**nodes;
	int		i;

	nodes = (t_node **)vec_sort(graph, sizeof(t_node), &node_cmp);
	if (!nodes)
		free_and_clear(graph);
	i = 0;
	while (nodes[i + 1])
	{
		if (ft_strequ(nodes[i]->name, nodes[i + 1]->name))
		{
			free(nodes);
			free_and_clear(graph);
		}
		i++;
	}
	return (nodes);
}

int		parse(int fd, t_nodevec *graph, t_node ***nodes)
{
	char	*line;
	int		num_ants;

	if (get_next_line(fd, &line) != 1)
		return (-1);
	num_ants = ft_atoi(line);
	ft_putendl(line);
	ft_strdel(&line);
	if ((line = add_all_nodes(fd, graph, line)) == NULL)
		return (-1);
	if (((*nodes) = clean_up(graph)) == NULL)
	{
		if (line)
			free(line);
		return (-1);
	}
	while (line)
	{
		ft_putendl(line);
		if (line[0] != '#')
			add_link(graph, (*nodes), line);
		ft_strdel(&line);
		get_next_line(fd, &line);
	}
	return (num_ants);
}

int		main(void)
{
	t_node		**nodes;
	t_nodevec	*graph;
	int			num_ants;

	graph = vecnew(NULL, sizeof(t_node));
	nodes = NULL;
	num_ants = parse(0, graph, &nodes);
	if (nodes == NULL || num_ants < 1)
	{
		ft_putendl("ERROR");
		free_graph(graph);
		return (-1);
	}
	find_path(nodes, num_ants);
	free_graph(graph);
	return (0);
}
