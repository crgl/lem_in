/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:46:26 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/11 16:46:53 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	traverse(char *link, t_node **nodes)
{
	char	**ends;
	char	*rev;

	dict_mod("mod", link, -1);
	ends = ft_strsplit(link, '-');
	rev = ft_sthreejoin(ends[1], "-", ends[0]);
	dict_mod("mod", rev, 1);
	find_node(nodes, ends[0])->visited |= EVER;
	find_node(nodes, ends[1])->visited |= EVER;
	free(ends[0]);
	free(ends[1]);
	free(ends);
	free(rev);
}

void	add_node_to_queue(char *new_link, t_path *found, t_node *to_inspect,
			t_queue *to_search)
{
	t_svec	*new_path;
	t_path	*to_add;

	new_path = vecnew(found->path->e, found->path->len);
	veccat(new_path, &new_link, sizeof(new_link));
	to_add = (t_path *)ft_memalloc(sizeof(t_path));
	to_add->current = to_inspect;
	to_add->entered_on_2 = (dict_mod("get", new_link, 0) == 2);
	to_add->path = new_path;
	q_add(to_search, ft_lstnew(&to_add, sizeof(to_add)));
}

void	adjust_capacities(t_node **nodes, int start_ind)
{
	t_path	*start_info;
	int		i;

	start_info = (t_path *)ft_memalloc(sizeof(t_path));
	start_info->current = nodes[start_ind];
	start_info->path = vecnew(NULL, sizeof(char *));
	start_info->entered_on_2 = 1;
	while (find_flow(q_new(ft_lstnew(&start_info, sizeof(start_info))),
								nodes, 0))
	{
		i = 0;
		while (nodes[i])
			nodes[i++]->visited &= ~NOW;
	}
	vecdel(&(start_info->path));
	free(start_info);
}

t_list	*make_list_of(t_npair old)
{
	t_node	*current;
	t_node	**ln;
	int		i;
	char	*link;
	t_list	*out;

	current = old[1];
	out = NULL;
	i = 0;
	while ((ln = (t_node **)get_element(current->links,
			sizeof(t_node *), i++)))
	{
		link = ft_sthreejoin(current->name, "-", (*ln)->name);
		if (dict_mod("get", link, 0) == 0)
			out = ft_lstnew(&((t_npair){old[0], *ln}), sizeof(t_npair));
		free(link);
		if (out)
			return (out);
	}
	return (NULL);
}

void	find_path(t_node **nodes, int num_ants)
{
	int		start_ind;
	t_npvec	*sequence;

	start_ind = -1;
	while (nodes[++start_ind])
		if (nodes[start_ind]->typ == start)
			break ;
	if (num_ants < 1 || !nodes[start_ind] || nodes[start_ind]->typ != start)
	{
		ft_putendl_fd("ERROR", 2);
		return ;
	}
	adjust_capacities(nodes, start_ind);
	sequence = vecnew(NULL, sizeof(t_npair));
	paths_from_start(nodes, start_ind, sequence);
	if (sequence->len == 0)
	{
		vecdel(&sequence);
		ft_putendl_fd("ERROR: No path to sink", 2);
		return ;
	}
	send_out(sequence, num_ants, NULL, NULL);
	vecdel(&sequence);
}
