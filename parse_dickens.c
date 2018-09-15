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

void	set_states(t_ptrmap **nodes, t_ptrmap **edges, char **links, int step)
{
	char	*node1;
	char	*node2;
	int		i;

	i = 0;
	while (links[i])
	{
		node1 = links[i] + 1;
		node2 = ft_strchr(links[i], '-') + 1;
		*ft_strchr(links[i], '-') = '\0';
		find_node(nodes, node1)->states[step] = true;
		find_node(nodes, node2)->states[step + 2] = true;
		find_edge(edges, node1, node2)->states[step + 1] = true;
		i++;
	}
}

int		parse_the_dickens(t_ptrmap **nodes, t_ptrmap **edges)
{
	int		step;
	char	*line;
	char	**links;

	step = 0;
	while (get_next_line(0, &line) == 1)
	{
		links = ft_strsplit(line, ' ');
		set_states(nodes, edges, links, step);
		step += 3;
		free_matrix((void ***)&links);
	}
	return (step);
}
