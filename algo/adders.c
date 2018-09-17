/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 13:21:03 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/15 13:21:09 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	add_link(t_nodevec *graph, t_node **nodes, char *line)
{
	t_node	*n1;
	t_node	*n2;
	char	*node2;
	char	*rev;

	if (!ft_strchr(line, '-'))
	{
		free(nodes);
		free_and_clear(graph);
	}
	dict_mod("set", ft_strdup(line), 1);
	node2 = ft_strchr(line, '-') + 1;
	*ft_strchr(line, '-') = '\0';
	n2 = find_node(nodes, node2);
	n1 = find_node(nodes, line);
	rev = ft_sthreejoin(node2, "-", line);
	dict_mod("set", rev, 1);
	if (!n1 || !n2)
	{
		free(nodes);
		free_and_clear(graph);
	}
	veccat(n1->links, &n2, sizeof(n2));
	veccat(n2->links, &n1, sizeof(n1));
}

void	add_node(t_nodevec *graph, char *line, t_nodetype typ)
{
	if (is_valid_node(line))
		veccat(graph, &((t_node){typ, 0, ft_strdup(line),
			vecnew(NULL, sizeof(t_node *))}),
			sizeof(t_node));
	else
		free_and_clear(graph);
}

int		add_special(int fd, t_nodevec *graph, char **line)
{
	t_nodetype	typ;

	typ = START_OR_END(*line);
	ft_strdel(line);
	get_next_line(fd, line);
	if (!*line)
		return (-1);
	ft_putendl(*line);
	add_node(graph, *line, typ);
	return (0);
}

int		is_link(char *line)
{
	if (ft_strchr(line, ' '))
	{
		if (ft_strchr(line, '-'))
		{
			if (ft_strchr(line, '-') - ft_strchr(line, ' ') < 0)
				return (1);
			else
				return (0);
		}
		else
			return (0);
	}
	else if (ft_strchr(line, '-'))
		return (1);
	return (0);
}

char	*add_all_nodes(int fd, t_nodevec *graph, char *line)
{
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strlen(line) < 2)
		{
			ft_strdel(&line);
			return (NULL);
		}
		if (is_link(line))
			break ;
		ft_putendl(line);
		if (line[0] != '#')
			add_node(graph, line, mid);
		else if (line[1] == '#')
			if (MARKS_START(line) || MARKS_END(line))
				if (add_special(fd, graph, &line) == -1)
					return (NULL);
		ft_strdel(&line);
	}
	return (line);
}
