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

char	*ft_sthreejoin(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*out;

	tmp = ft_strjoin(s1, s2);
	out = ft_strjoin(tmp, s3);
	if (tmp)
		free(tmp);
	return (out);
}

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
	ft_putendl_fd("Invalid input!", 2);
	exit(-1);
}

int		node_cmp(void *n1, void *n2)
{
	return (ft_strcmp(((t_node *)n1)->name, ((t_node *)n2)->name));
}

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
	int	len;
	int	i;
	int	upper;
	int	lower;

	len = ft_len((void **)nodes);
	i = len / 2;
	upper = len - 1;
	lower = 0;
	if (ft_strequ(key, nodes[0]->name))
		return (nodes[0]);
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

int		parse(int fd, t_nodevec *graph, t_node ***nodes)
{
	char	*line;
	int		num_ants;

	if (get_next_line(fd, &line) == 1)
		num_ants = ft_atoi(line);
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
