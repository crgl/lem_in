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

void	free_graph(t_nodevec *graph)
{
	t_node			*loc;
	unsigned long	i;

	loc = (t_node *)graph->e;
	i = 0;
	while (i < graph->cap / sizeof(t_node))
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

int		ft_len(void **arr)
{
	int	i;

	i = 0;
	while (*arr++ != NULL)
		i++;
	return (i);
}

t_node	*find_node(t_node **nodes, char *key)
{
	int	len;
	int	i;
	int	diff;

	len = ft_len((void **)nodes);
	i = len / 2;
	diff = len / 4;
	if (ft_strequ(key, nodes[0]->name))
		return (nodes[0]);
	while (i != 0 && nodes[i])
	{
		if (ft_strequ(key, nodes[i]->name))
			return (nodes[i]);
		if (ft_strcmp(key, nodes[i]->name) < 0)
			i -= diff;
		else
			i += diff;
		diff /= 2;
	}
	return (NULL);
}

void	add_link(t_nodevec *graph, t_node **nodes, char *line)
{
	t_node	*n1;
	t_node	*n2;

	if (!ft_strchr(line, '-'))
	{
		free(nodes);
		free_and_clear(graph);
	}
	n2 = find_node(nodes, ft_strchr(line, '-') + 1);
	*ft_strchr(line, '-') = '\0';
	n1 = find_node(nodes, line);
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
	if (ft_strchr(line, ' ') || ft_strchr(ft_strchr(line, ' ') + 1, ' '))
		*ft_strchr(line, ' ') = '\0';
	if (is_valid_node(line))
		veccat(graph, &((t_node){typ, ft_strdup(line), vecnew(NULL, sizeof(t_node *))}), sizeof(t_node));
	else
		free_and_clear(graph);
}

t_node	**parse(int fd, t_nodevec *graph)
{
	char	*line;
	t_node	**nodes;
	int		num_ants;

	if (get_next_line(fd, &line) == 1)
		num_ants = ft_atoi(line);
	else
		return (NULL);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		if (ft_strlen(line) < 2)
			return (NULL);
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
				add_node(graph, line, start);
			}
			else if (ft_strequ(line + 2, "end"))
			{
				ft_strdel(&line);
				get_next_line(fd, &line);
				add_node(graph, line, end);
			}
		}
		free(line);
	}
	if ((nodes = clean_up(graph)) == NULL)
	{
		free(line);
		return (NULL);
	}
	if (line[0] != '#')
		add_link(graph, nodes, line);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		if (line[0] != '#')
			add_link(graph, nodes, line);
		free(line);
	}
	return (nodes);
}

int		main(void)
{
	t_node		**nodes;
	t_nodevec	*graph;

	graph = vecnew(NULL, sizeof(t_node));
	nodes = parse(0,  graph);
	if (graph == NULL)
	{
		ft_putendl_fd("Invalid input!", 2);
		free_graph(graph);
		return (-1);
	}
	find_path(nodes, graph);
	free_graph(graph);
	return (0);
}
