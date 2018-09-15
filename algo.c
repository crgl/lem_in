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

void	search_and_destroy(t_queue *to_search, t_path *found, t_svec *to_free)
{
	int		i;
	char	**freeable;
	t_list	*this_too;
	t_path	*also_this;

	i = 0;
	while ((freeable = (char **)get_element(to_free, sizeof(char *), i++)))
		free(*freeable);
	if (found->current->typ != start)
	{
		vecdel(&(found->path));
		free(found);
	}
	while ((this_too = q_pop(to_search)))
	{
		also_this = *((t_path **)(this_too->content));
		also_this->current->visited &= ~NOW;
		vecdel(&(also_this->path));
		free(also_this);
		free(this_too);
	}
	free(to_search);
}

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

char	*inspect_link(t_node **nodes, t_queue *to_search, t_path *found,
						t_node *to_inspect)
{
	int		i;
	char	**link;
	char	*new_link;

	new_link = ft_sthreejoin(found->current->name, "-", to_inspect->name);
	if (dict_mod("get", new_link, 0) != 0)
	{
		if (to_inspect->typ == end)
		{
			i = 0;
			while ((link = (char **)get_element(found->path,
										sizeof(char *), i++)))
				traverse(*link, nodes);
			traverse(new_link, nodes);
			free(new_link);
			return (NULL);
		}
		else if (AVAIL(to_inspect) && (UNRESTRICTED(found) || REV(new_link)))
		{
			add_node_to_queue(new_link, found, to_inspect, to_search);
			if (dict_mod("get", new_link, 0) == 2 || OFF_PATH(to_inspect))
				to_inspect->visited |= NOW;
		}
	}
	return (new_link);
}

t_path	*get_current_path(t_queue *to_search, t_svec **to_free)
{
	t_list	*next_node;
	t_path	*found;

	if (to_search->start == NULL)
		return (NULL);
	if (!*to_free)
		*to_free = vecnew(NULL, sizeof(char *));
	next_node = q_pop(to_search);
	found = *((t_path **)(next_node->content));
	free(next_node);
	return (found);
}

int		find_flow(t_queue *to_search, t_node **nodes)
{
	static t_svec	*to_free;
	t_path			*found;
	size_t			i;
	t_node			**to_inspect;
	char			*new_link;

	if ((found = get_current_path(to_search, &to_free)) == NULL)
		return (0);
	i = 0;
	while ((to_inspect = (t_node **)get_element(found->current->links,
										sizeof(t_node *), i++)))
	{
		if ((new_link = inspect_link(nodes, to_search, found,
							*to_inspect)) == NULL)
		{
			search_and_destroy(to_search, found, to_free);
			vecdel(&to_free);
			return (1);
		}
		if (dict_mod("get", new_link, 0) != 0)
			veccat(to_free, &new_link, sizeof(char *));
		else
			free(new_link);
	}
	return (find_flow(to_search, nodes));
}

void	adjust_capacities(t_node **nodes, int start_ind)
{
	t_path	*start_info;
	int		i;

	start_info = (t_path *)ft_memalloc(sizeof(t_path));
	start_info->current = nodes[start_ind];
	start_info->path = vecnew(NULL, sizeof(char *));
	start_info->entered_on_2 = 1;
	while (find_flow(q_new(ft_lstnew(&start_info, sizeof(start_info))), nodes))
	{
		i = 0;
		while (nodes[i])
			nodes[i++]->visited &= ~NOW;
	}
}

t_list	*make_list_of(t_npair just_traveled)
{
	t_node	*current;
	t_node	**ln;
	int		i;
	char	*link;
	t_list	*out;

	current = just_traveled[1];
	out = NULL;
	i = 0;
	while ((ln = (t_node **)get_element(current->links,
			sizeof(t_node *), i++)))
	{
		link = ft_sthreejoin(current->name, "-", (*ln)->name);
		if (dict_mod("get", link, 0) == 0)
			out = ft_lstnew(&((t_npair){current, *ln}), sizeof(t_npair));
		free(link);
		if (out)
			return (out);
	}
	return (NULL);
}

void	print_and_free(t_queue *rows)
{
	t_list	*ln;
	t_npair	*nodes;
	int		i;

	i = 0;
	while ((ln = q_pop(rows)) != NULL)
	{
		if (ln->content != NULL)
		{
			nodes = (t_npair *)(ln->content);
			ft_printf("%.*sL%s-%s", i, " ",
						(*nodes)[0]->name, (*nodes)[1]->name);
			free(nodes);
			i = 1;
		}
		else
		{
			ft_printf("\n");
			i = 0;
		}
		free(ln);
	}
	free(rows);
}

void	send_out(t_npvec *sequence, int num_ants, t_list *oldrow, t_list *row)
{
	t_npair	*seq_e;
	t_queue	*ant_plan;
	int		i;

	ant_plan = q_new(NULL);
	while (num_ants > 0 || oldrow)
	{
		row = NULL;
		i = 0;
		while ((seq_e = (t_npair *)get_element(sequence, sizeof(t_npair), i))
				&& i++ < num_ants)
			ft_lstadd(&row, ft_lstnew(seq_e, sizeof(t_npair)));
		while (oldrow)
		{
			ft_lstadd(&row, make_list_of(*(t_npair *)(oldrow->content)));
			oldrow = oldrow->next;
		}
		q_add(ant_plan, ft_lstnew(NULL, 0));
		q_add(ant_plan, row);
		oldrow = row;
		num_ants -= sequence->len / sizeof(t_npair);
	}
	print_and_free(ant_plan);
}

void	paths_from_start(t_node **nodes, int start_ind, t_npvec *sequence)
{
	int		i;
	t_node	**ln;
	char	*link;

	i = 0;
	while ((ln = (t_node **)get_element(nodes[start_ind]->links,
			sizeof(t_node *), i++)))
	{
		link = ft_sthreejoin(nodes[start_ind]->name, "-", (*ln)->name);
		if (dict_mod("get", link, 0) == 0)
			veccat(sequence, &((t_npair){nodes[start_ind], *ln}),
					sizeof(t_npair));
		free(link);
	}
}

void	find_path(t_node **nodes, int num_ants)
{
	int		start_ind;
	t_npvec	*sequence;

	start_ind = -1;
	while (nodes[++start_ind])
		if (nodes[start_ind]->typ == start)
			break ;
	if (num_ants < 1 || nodes[start_ind]->typ != start)
		return ;
	adjust_capacities(nodes, start_ind);
	sequence = vecnew(NULL, sizeof(t_npair));
	paths_from_start(nodes, start_ind, sequence);
	if (sequence->len == 0)
	{
		free(sequence);
		ft_putendl_fd("ERROR: No path to sink", 2);
		return ;
	}
	send_out(sequence, num_ants, NULL, NULL);
	free(sequence);
}
