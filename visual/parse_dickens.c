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

void	set_states(t_ptrmap ***nodedges, char ***links, int step,
					t_ptrmap *start)
{
	char	*node1;
	char	*node2;
	int		i;
	int		j;
	size_t	len;

	i = -1;
	while (links[0][++i])
	{
		len = ft_strchr(links[0][i], '-') - links[0][i] + 1;
		node1 = start->names[0];
		j = -1;
		while (links[1] && links[1][++j])
		{
			if (ft_strncmp(links[1][j], links[0][i], len) == 0)
			{
				node1 = ft_strchr(links[1][j], '-') + 1;
				break ;
			}
		}
		node2 = ft_strchr(links[0][i], '-') + 1;
		find_node(nodedges[0], node1)->states[step] = true;
		find_node(nodedges[0], node2)->states[step + 2] = true;
		find_edge(nodedges[1], node1, node2)->states[step + 1] = true;
	}
}

int		parse_the_dickens(t_ptrmap **nodes, t_ptrmap **edges)
{
	int			step;
	char		*line;
	char		**links[2];
	t_ptrmap	*start_node;
	t_ptrmap	**nodedges[2];

	step = 0;
	start_node = nodes[step];
	while (start_node->inactive != SN_INACT)
		start_node = nodes[++step];
	ft_memcpy(nodedges, (t_ptrmap **[]){nodes, edges}, 2 * sizeof(void *));
	step = 0;
	links[1] = NULL;
	while (get_next_line(0, &line) == 1)
	{
		links[0] = ft_strsplit(line, ' ');
		set_states(nodedges, links, step, start_node);
		step += 3;
		if (links[1])
			free_matrix((void ***)&links[1]);
		links[1] = links[0];
		free(line);
	}
	free_matrix((void ***)&links[1]);
	return (step);
}

void	parse_command(t_pmvec *doubleedges, char **line)
{
	if (line && doubleedges)
		return ;
}
