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
	while (line[++i])
		if (line[i] == '-')
			return (0);
	return (1);
}

t_ptrmap	*find_node(t_ptrmap **nodes, char *key)
{
	int	i;
	int	upper;
	int	lower;

	i = ft_len((void **)nodes) / 2;
	upper = ft_len((void **)nodes) - 1;
	lower = 0;
	while (upper != lower)
	{
		if (ft_strequ(key, nodes[i]->names[0]))
			return (nodes[i]);
		if (ft_strcmp(key, nodes[i]->names[0]) < 0)
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
	if (ft_strequ(key, nodes[i]->names[0]))
		return (nodes[i]);
	return (NULL);
}

void	add_link(t_ptrmap **nodes, t_pmvec *doubleedges, char *line)
{
	t_ptrmap	*the_stuff;
	char		*node2;
	char		*tmp;
	
	node2 = ft_strchr(line, '-') + 1;
	*ft_strchr(line, '-') = '\0';
	if (!find_node(nodes, line) || !find_node(nodes, node2))
	{
ft_printf("There seems to be... trouble\n");
		free(doubleedges);
		exit(-1);
	}
	the_stuff = (t_ptrmap *)ft_memalloc(sizeof(t_ptrmap));
	the_stuff->active = E_ACT;
	the_stuff->inactive = E_INACT;
	if (ft_strcmp(node2, line) < 0)
	{
		tmp = line;
		line = node2;
		node2 = tmp;
	}
	the_stuff->coords[0][0] = find_node(nodes, line)->coords[0][0];
	the_stuff->coords[0][1] = find_node(nodes, line)->coords[0][1];
	the_stuff->coords[1][0] = find_node(nodes, node2)->coords[0][0];
	the_stuff->coords[1][1] = find_node(nodes, node2)->coords[0][1];
	the_stuff->names[0] = ft_strdup(line);
	the_stuff->names[1] = ft_strdup(node2);
	veccat(doubleedges, the_stuff, sizeof(t_ptrmap));
	free(the_stuff);
}

int		edge_cmp(void *n1, void *n2)
{
	if (ft_strcmp(((t_ptrmap *)n1)->names[0], ((t_ptrmap *)n2)->names[0]) != 0)
		return (ft_strcmp(((t_ptrmap *)n1)->names[0], ((t_ptrmap *)n2)->names[0]));
	else
		return (ft_strcmp(((t_ptrmap *)n1)->names[1], ((t_ptrmap *)n2)->names[1]));
}

int		node_cmp(void *n1, void *n2)
{
	return (ft_strcmp(((t_ptrmap *)n1)->names[0], ((t_ptrmap *)n2)->names[0]));
}

t_ptrmap	**edge_clean(t_pmvec *doubleedges)
{
	t_ptrmap	**edges;
	int		i;

	edges = (t_ptrmap **)vec_sort(doubleedges, sizeof(t_ptrmap), &edge_cmp);
	if (!edges)
		free(doubleedges);
	return (edges);
}

t_ptrmap	**clean_up(t_pmvec *doublenodes)
{
	t_ptrmap	**nodes;
	int		i;

	nodes = (t_ptrmap **)vec_sort(doublenodes, sizeof(t_ptrmap), &node_cmp);
	if (!nodes)
		free(doublenodes);
	i = 0;
	while (nodes[i + 1])
	{
		if (ft_strequ(nodes[i]->names[0], nodes[i + 1]->names[0]))
		{
			free(nodes);
			free(doublenodes);
		}
		i++;
	}
	return (nodes);
}

void	add_node(t_pmvec *doublenodes, char *line, int inactive, int active)
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
ft_printf("There seems to be... trouble\n");
		free(doublenodes);
		exit(-1);
	}
}

void	normalize(t_ptrmap **nodes)
{
	int max_x;
	int min_x;
	int max_y;
	int min_y;
	int i;
	
	i = 0;
	max_x = INT_MIN;
	max_y = INT_MIN;
	min_x = INT_MAX;
	min_y = INT_MAX;
	while ((nodes[i]) != NULL)
	{
		if (nodes[i]->coords[0][0] > max_x)
			max_x = nodes[i]->coords[0][0];
		if (nodes[i]->coords[0][0] < min_x)
			min_x = nodes[i]->coords[0][0];
		if (nodes[i]->coords[0][1] > max_y)
			max_y = nodes[i]->coords[0][1];
		if (nodes[i]->coords[0][1] < min_y)
			min_y = nodes[i]->coords[0][1];
		i++;
	}
	i = 0;
	while ((nodes[i]) != NULL)
	{
		nodes[i]->coords[0][0] = (nodes[i]->coords[0][0] - (LL)min_x) * (LL)199 / max_x;
		nodes[i]->coords[0][1] = (nodes[i]->coords[0][1] - (LL)min_y) * (LL)49 / max_y;
		i++;
	}
}

int		parse(t_pmvec *doublenodes, t_pmvec *doubleedges, t_ptrmap ***nodes, t_ptrmap ***edges)
{
	char	*line;
	int		num_ants;

	if (get_next_line(0, &line) == 1)
		num_ants = ft_atoi(line);
	else
		return (-1);
	ft_strdel(&line);
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strlen(line) < 2)
			return (-1);
		if (ft_strchr(line, '-'))
			break ;
		if (line[0] != '#')
			add_node(doublenodes, line, MN_INACT, MN_ACT);
		else if (line[1] == '#')
		{
			if (ft_strequ(line + 2, "start"))
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				if (!line)
					return (-1);
				add_node(doublenodes, line, SN_INACT, SN_ACT);
			}
			else if (ft_strequ(line + 2, "end"))
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				if (!line)
					return (-1);
				add_node(doublenodes, line, EN_INACT, EN_ACT);
			}
		}
		ft_strdel(&line);
	}
	if ((*nodes = clean_up(doublenodes)) == NULL)
	{
		if (line)
			free(line);
		return (-1);
	}
	normalize(*nodes);
	if (line && line[0] != '#')
		add_link(*nodes, doubleedges, line);
	if (line)
		ft_strdel(&line);
	while (get_next_line(0, &line) == 1)
	{
		if (!line[0])
		{
			free(line);
			break ;
		}
		if (line[0] != '#')
		{
			add_link(*nodes, doubleedges, line);
		}
		ft_strdel(&line);
	}
	if (((*edges) = edge_clean(doubleedges)) == NULL)
		return (-1);
	return (num_ants);
}

void	free_everything(t_ptrmap **nodes, t_ptrmap **edges, t_pmvec *doublenodes, t_pmvec *doubleedges)
{
	free(nodes);
	free(edges);
	vecdel(&doubleedges);
	vecdel(&doublenodes);
}

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

void	fill_between(char *map, t_ptrmap ***annotate, t_ptrmap *edge)
{
	int x_start;
	int y_start;

	x_start = edge->coords[0][0];
	y_start = edge->coords[0][1];
	while (x_start < edge->coords[1][0])
	{
		if (map[x_start + edge->coords[0][1] * 201] == ' ')
			map[x_start + edge->coords[0][1] * 201] = '=';
		add_to_annotation(annotate, edge, x_start + edge->coords[0][1] * 201);
		x_start++;
	}
	while (y_start < edge->coords[1][1])
	{
		if (map[edge->coords[1][0] + y_start * 201] == ' ')
			map[edge->coords[1][0] + y_start * 201] = '|';
		add_to_annotation(annotate, edge, edge->coords[1][0] + y_start * 201);
		y_start++;
	}
	while (x_start > edge->coords[1][0])
	{
		if (map[x_start + edge->coords[0][1] * 201] == ' ')
			map[x_start + edge->coords[0][1] * 201] = '=';
		add_to_annotation(annotate, edge, x_start + edge->coords[0][1] * 201);
		x_start--;
	}
	while (y_start > edge->coords[1][1])
	{
		if (map[edge->coords[1][0] + y_start * 201] == ' ')
			map[edge->coords[1][0] + y_start * 201] = '|';
		add_to_annotation(annotate, edge, edge->coords[1][0] + y_start * 201);
		y_start--;
	}
}

int		parse_the_dickens(t_ptrmap **nodes, t_ptrmap **edges)
{
	int	step;
	char *line;

	step = 0;
	(void)nodes;
	(void)edges;
	return (1);
}

char	*make_color(unsigned int color)
{
	char	*r;
	char	*g;
	char	*b;
	char	*out;
	char	*tmp;

	r = ft_itoa((int)((color >> 16) & 0xFF));
	g = ft_itoa((int)((color >> 8) & 0xFF));
	b = ft_itoa((int)((color) & 0xFF));
	tmp = ft_sthreejoin("\033[38;2;", r, ";");
	out = ft_sthreejoin(tmp, g, ";");
	free(tmp);
	tmp = ft_sthreejoin(out, b, "m");
	free(out);
	free(r);
	free(g);
	free(b);
	return (tmp);
}

void	print_the_dickens(char *map, t_ptrmap ***annotate, int num_steps)
{
	int				step;
	t_svec			*to_print;
	int				i;
	int				j;
	unsigned int	current_color;
	unsigned int	new_color;
	bool			active;
	char			*ansi;

	step = 0;
	while (step < num_steps)
	{
		current_color = EN_INACT;
		new_color = EN_INACT;
		to_print = vecnew("\033[J\033[38;2;127;0;0m", 18 * sizeof(char));
		i = 0;
		while (map[i])
		{
			if (annotate[i] == NULL)
				veccat(to_print, map + i, sizeof(char));
			else
			{
				active = false;
				j = 0;
				while (annotate[i][j])
				{
					if (annotate[i][j]->states[step])
					{
						active = true;
						new_color = annotate[i][j]->active;
					}
					else if (active == false)
					{
						new_color = annotate[i][j]->inactive;
					}
					j++;
				}
				if (new_color != current_color)
				{
					ansi = make_color(new_color);
					veccat(to_print, ansi, ft_strlen(ansi) * sizeof(char));
					current_color = new_color;
					ft_strdel(&ansi);
				}
				veccat(to_print, map + i, sizeof(char));
			}
			i++;
		}
		ansi = vec2str(to_print);
		ft_putstr(ansi);
		ft_putstr(map);
		ft_strdel(&ansi);
		vecdel(&to_print);
		step++;
	}
}

void	execute(t_ptrmap **nodes, t_ptrmap **edges, int num_ants)
{
	char		*map;
	t_ptrmap	***annotate;
	int			i;
	int			j;
	int			num_steps;

	map = (char *)ft_memalloc((201 * 50 + 1) * sizeof(char));
	annotate = (t_ptrmap ***)ft_memalloc((201 * 50 + 1) * sizeof(t_ptrmap **));
	ft_memset(map, ' ', (201 * 50));
	i = 0;
	while (i < 50)
		map[201 * i++ + 200] = '\n';
	i = 0;
	while (nodes[i])
	{
		if (nodes[i]->states == NULL)
			nodes[i]->states = (bool *)ft_memalloc((num_ants + ft_len((void **)nodes)) * 2 * sizeof(bool));
		if (map[nodes[i]->coords[0][0] + nodes[i]->coords[0][1] * 201] == ' ')
			map[nodes[i]->coords[0][0] + nodes[i]->coords[0][1] * 201] = '@';
		add_to_annotation(annotate, nodes[i], nodes[i]->coords[0][0] + nodes[i]->coords[0][1] * 201);
		i++;
	}
	i = 0;
	while (edges[i])
	{
		if (edges[i]->states == NULL)
			edges[i]->states = (bool *)ft_memalloc((num_ants + ft_len((void **)nodes)) * 2 * sizeof(bool));
		fill_between(map, annotate, edges[i++]);
	}
	num_steps = parse_the_dickens(nodes, edges);
	ft_putstr(map);
	print_the_dickens(map, annotate, num_steps);
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
		free_everything(nodes, edges, doublenodes, doubleedges);
		return (-1);
	}
	execute(nodes, edges, num_ants);
	free_everything(nodes, edges, doublenodes, doubleedges);
	return (0);
}
