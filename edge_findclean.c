/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_findclean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:48:38 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/15 12:48:49 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int			edge_cmp(void *n1, void *n2)
{
	if (ft_strcmp(((t_ptrmap *)n1)->names[0],
		((t_ptrmap *)n2)->names[0]) != 0)
		return (ft_strcmp(((t_ptrmap *)n1)->names[0],
			((t_ptrmap *)n2)->names[0]));
	else
		return (ft_strcmp(((t_ptrmap *)n1)->names[1],
			((t_ptrmap *)n2)->names[1]));
}

t_ptrmap	**edge_clean(t_pmvec *d_edges)
{
	t_ptrmap	**edges;

	edges = (t_ptrmap **)vec_sort(d_edges, sizeof(t_ptrmap), &edge_cmp);
	if (!edges)
		free(d_edges);
	return (edges);
}

t_ptrmap	*isolate(t_ptrmap **edges, char *key1, char *key2, int set[2])
{
	int i;

	i = ft_len((void **)edges) / 2;
	while (set[1] != set[0])
	{
		if (ft_strequ(key1, edges[i]->names[0]) &&
			ft_strequ(key2, edges[i]->names[1]))
			return (edges[i]);
		if (ft_strcmp(key1, edges[i]->names[0]) < 0 ||
			(ft_strcmp(key1, edges[i]->names[0]) == 0 &&
			ft_strcmp(key2, edges[i]->names[1]) < 0))
		{
			set[1] = i;
			i = (i + set[0] - 1) / 2;
		}
		else
		{
			set[0] = i;
			i = (i + set[1] + 1) / 2;
		}
	}
	if (ft_strequ(key1, edges[i]->names[0]) &&
		ft_strequ(key2, edges[i]->names[1]))
		return (edges[i]);
	return (NULL);
}

t_ptrmap	*find_edge(t_ptrmap **edges, char *key1, char *key2)
{
	int		set[2];
	char	*tmp;

	set[1] = ft_len((void **)edges) - 1;
	set[0] = 0;
	if (ft_strcmp(key1, key2) > 0)
	{
		tmp = key1;
		key1 = key2;
		key2 = tmp;
	}
	return (isolate(edges, key1, key2, set));
}
