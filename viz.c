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

void	add_node(t_nodevec *graph, char *line, t_nodetype typ)
{
	if (is_valid_node(line))
		veccat(graph, &((t_node){typ, 0, ft_strdup(line),
			vecnew(NULL, sizeof(t_node *))}),
			sizeof(t_node));
	else
		free_and_clear(graph);
}

int		parse(int fd, t_nodevec *graph, t_node ***nodes)
{
	char	*line;
	int		num_ants;

	if (get_next_line(fd, &line) == 1)
	{
		num_ants = ft_atoi(line);
		ft_putendl(line);
	}
	else
		return (-1);
	ft_strdel(&line);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		if (ft_strlen(line) < 2)
			return (-1);
		if (ft_strchr(line, '-'))
			break ;
		if (line[0] != '#')
			add_node(graph, line, mid);
		else if (line[1] == '#')
		{
			if (ft_strequ(line + 2, "start"))
			{
				ft_strdel(&line);
				get_next_line(fd, &line);
				if (!line)
					return (-1);
				ft_putendl(line);
				add_node(graph, line, start);
			}
			else if (ft_strequ(line + 2, "end"))
			{
				ft_strdel(&line);
				get_next_line(fd, &line);
				if (!line)
					return (-1);
				ft_putendl(line);
				add_node(graph, line, end);
			}
		}
		ft_strdel(&line);
	}
	if (((*nodes) = clean_up(graph)) == NULL)
	{
		free(line);
		return (-1);
	}
	if (line[0] != '#')
		add_link(graph, (*nodes), line);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		if (line[0] != '#')
			add_link(graph, (*nodes), line);
		ft_strdel(&line);
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
		ft_putendl_fd("Invalid input!", 2);
		free_graph(graph);
		return (-1);
	}
	find_path(nodes, num_ants);
	free_graph(graph);
	return (0);
}
