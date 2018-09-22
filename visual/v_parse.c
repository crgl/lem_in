/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 11:45:50 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/15 11:46:01 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int		set_ends(t_pmvec *doublenodes, char **line)
{
	if (ft_strequ(*line + 2, "start"))
	{
		ft_strdel(line);
		get_next_line(0, line);
		if (!*line)
			return (-1);
		add_node(doublenodes, *line, SN_INACT, SN_ACT);
	}
	else if (ft_strequ(*line + 2, "end"))
	{
		ft_strdel(line);
		get_next_line(0, line);
		if (!*line)
			return (-1);
		add_node(doublenodes, *line, EN_INACT, EN_ACT);
	}
	return (1);
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

int		parse_node(t_pmvec *doublenodes, char **line)
{
	while (get_next_line(0, line) == 1)
	{
		if (ft_strnequ(*line, "ERROR", 5))
		{
			free(*line);
			return (-1);
		}
		if (ft_strlen(*line) < 2)
			return (-1);
		if (is_link(*line))
			return (1);
		if ((*line)[0] != '#')
			add_node(doublenodes, *line, MN_INACT, MN_ACT);
		else if ((*line)[1] == '#')
		{
			if (set_ends(doublenodes, line) == -1)
				return (-1);
		}
		ft_strdel(line);
	}
	return (1);
}

void	parse_edges(t_pmvec *doubleedges, t_ptrmap **nodes, char **line)
{
	if (*line && (*line)[0] != '#')
		add_link(nodes, doubleedges, *line);
	if (*line)
		ft_strdel(line);
	while (get_next_line(0, line) == 1)
	{
		if (!*line[0])
		{
			free(*line);
			return ;
		}
		if ((*line)[0] != '#')
			add_link(nodes, doubleedges, *line);
		else if ((*line)[1] == '#')
			parse_command(doubleedges, line);
		ft_strdel(line);
	}
}

int		parse(t_pmvec *doublenodes, t_pmvec *doubleedges,
			t_ptrmap ***nodes, t_ptrmap ***edges)
{
	char	*line;
	int		num_ants;

	if (get_next_line(0, &line) == 1)
		num_ants = ft_atoi(line);
	else
		return (-1);
	ft_strdel(&line);
	if (parse_node(doublenodes, &line) == -1)
		return (-1);
	if ((*nodes = clean_up(doublenodes)) == NULL)
	{
		if (line)
			free(line);
		return (-1);
	}
	normalize(*nodes);
	parse_edges(doubleedges, *nodes, &line);
	if (((*edges) = edge_clean(doubleedges)) == NULL)
		return (-1);
	return (num_ants);
}
