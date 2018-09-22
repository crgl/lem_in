/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dickens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 11:22:04 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/15 11:22:07 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	set_states(t_ptrmap **nodes, t_ptrmap **edges, char **links, int step, char **old_links,
					t_ptrmap *start)
{
	char	*node1;
	char	*node2;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (links[i])
	{
		len = ft_strchr(links[i], '-') - links[i] + 1;
		node1 = start->names[0];
		j = 0;
		while (old_links && old_links[j])
		{
			if (ft_strncmp(old_links[j], links[i], len) == 0)
			{
				node1 = ft_strchr(old_links[j], '-') + 1;
				break ;
			}
			j++;
		}
		node2 = ft_strchr(links[i], '-') + 1;
		find_node(nodes, node1)->states[step] = true;
		find_node(nodes, node2)->states[step + 2] = true;
		find_edge(edges, node1, node2)->states[step + 1] = true;
		i++;
	}
}

int		parse_the_dickens(t_ptrmap **nodes, t_ptrmap **edges)
{
	int			step;
	char		*line;
	char		**links;
	char		**old_links;
	t_ptrmap	*start_node;

	step = 0;
	start_node = nodes[step];
	while (start_node->inactive != SN_INACT)
		start_node = nodes[++step];
	step = 0;
	old_links = NULL;
	while (get_next_line(0, &line) == 1)
	{
		links = ft_strsplit(line, ' ');
		set_states(nodes, edges, links, step, old_links, start_node);
		step += 3;
		if (old_links)
			free_matrix((void ***)&old_links);
		old_links = links;
		free(line);
	}
	return (step);
}

void	parse_command(t_pmvec *doubleedges, char **line)
{
	if (line && doubleedges)
		return ;
}
