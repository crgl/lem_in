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

	dict_mod("mod", link, 0);
	ends = ft_strsplit(link, '-');
	rev = ft_sthreejoin(ends[1], "-", ends[0]);
	dict_mod("mod", rev, 2);
	find_node(nodes, ends[0])->visited |= EVER;
	find_node(nodes, ends[1])->visited |= EVER;
	free(ends[0]);
	free(ends[1]);
	free(ends);
	free(rev);
}

int	find_flow(t_queue *to_search, t_node **nodes)
{
	t_path			*found;
	size_t			i;
	t_list			*next_node;
	int				out;
	t_node			**to_inspect;
	char			**link;
	char			*new_link;
	t_svec			*new_path;
	t_path			*new_nameless_var;

	if (!to_search)
		return (0);
	next_node = q_pop(to_search);
	found = *((t_path **)(next_node->content));
	i = 0;
	while ((to_inspect = (t_node **)get_element(found->current->links, sizeof(t_node *), i++)))
	{
		new_link = ft_sthreejoin(found->current->name, "-", (*to_inspect)->name);
		if (dict_mod("get", new_link, 0) == 0)
		{
			free(new_link);
			continue ;
		}
		(*to_inspect)->visited |= NOW;
		if ((*to_inspect)->typ == end)
		{
			i = 0;
			while ((link = (char **)get_element(found->path, sizeof(char *), i++)))
				traverse(*link, nodes);
			traverse(new_link, nodes);
			search_and_destroy(to_search);
			free(new_link);
			return (1);
		}
		else if ((*to_inspect)->typ == mid)
		{
			new_path = vecnew(found->path->e, found->path->len);
			veccat(new_path, &new_link, sizeof(new_link));
			new_nameless_var = (t_path *)ft_memalloc(sizeof(t_path));
			new_nameless_var->current = *to_inspect;
			new_nameless_var->entered_on_2 = (dict_mod("get", new_link, 0) == 2);
			new_nameless_var->path = new_path;
			q_add(to_search, ft_lstnew(&new_nameless_var, sizeof(new_nameless_var)));
		}
	}
	out = find_flow(to_search, nodes);
	i = 0;
	while ((to_inspect = (t_node **)get_element(found->current->links, sizeof(t_node *), i++)))
		(*to_inspect)->visited &= ~NOW;
	free(next_node);
	return (out);
}

void	adjust_capacities(t_node **nodes, int start_ind)
{
	t_path	*start_info;

	start_info = (t_path *)ft_memalloc(sizeof(t_path));
	start_info->current = nodes[start_ind];
	start_info->path = vecnew(NULL, sizeof(char *));
	while (find_flow(q_new(ft_lstnew(&start_info, sizeof(start_info))), nodes))
		;
}

void	send_out(t_node **nodes, t_npvec *sequence, int maximum)
{
	return ;
}

void	find_path(t_node **nodes, t_nodevec *graph, int num_ants)
{
	int		start_ind;
	int		i;
	t_node	*ln;
	t_npvec	*sequence;
	char	*link;

	start_ind = 0;
	while (nodes[start_ind])
	{
		if (nodes[start_ind]->typ == start)
			break ;
		start_ind++;
	}
	if (num_ants < 1)
		return ;
	adjust_capacities(nodes, start_ind);
	sequence = vecnew(NULL, sizeof(t_npair));
	i = 0;
	while ((ln = (t_node *)get_element(nodes[start_ind]->links,
			sizeof(t_node *), i++)))
	{
		link = ft_sthreejoin(nodes[start_ind]->name, "-", ln->name);
		if (dict_mod("get", link, 0) == 0)
			veccat(sequence, &((t_npair){nodes[start_ind], ln}), sizeof(t_npair));
		free(link);
	}
	while (num_ants > 0)
	{
		send_out(nodes, sequence, num_ants);
		num_ants -= ft_len((void **)sequence);
	}
	free(sequence);
}
