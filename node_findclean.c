/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_findclean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 13:16:32 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/15 13:16:43 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

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

int			node_cmp(void *n1, void *n2)
{
	return (ft_strcmp(((t_ptrmap *)n1)->names[0], ((t_ptrmap *)n2)->names[0]));
}

t_ptrmap	**clean_up(t_pmvec *doublenodes)
{
	t_ptrmap	**nodes;
	int			i;

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
