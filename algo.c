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
	char	*freeable;
	t_list	*this_too;
	t_path	*also_this;

	i = 0;
	while ((freeable = (char *)get_element(to_free, sizeof(char *), i++)))
		free(freeable);
	vecdel(&(found->path));
	free(found);
	while ((this_too = q_pop(to_search)))
	{
		also_this = *((t_path **)(this_too->content));
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
	static t_svec	*to_free;
	t_path			*found;
	size_t			i;
	t_list			*next_node;
	int				out;
	t_node			**to_inspect;
	char			**link;
	char			*new_link;
	t_svec			*new_path;
	t_path			*new_nameless_var;

	if (to_search->start == NULL)
		return (0);
	if (!to_free)
		to_free = vecnew(NULL, sizeof(char *));
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
		if ((*to_inspect)->typ == end)
		{
			i = 0;
			while ((link = (char **)get_element(found->path, sizeof(char *), i++)))
				traverse(*link, nodes);
			traverse(new_link, nodes);
			search_and_destroy(to_search, found, to_free);
			free(new_link);
			return (1);
		}
		else if ((*to_inspect)->typ == mid && ((*to_inspect)->visited & NOW) == 0 &&
					(((*to_inspect)->visited & EVER) == 0 || found->entered_on_2))
		{
			new_path = vecnew(found->path->e, found->path->len);
			veccat(new_path, &new_link, sizeof(new_link));
			new_nameless_var = (t_path *)ft_memalloc(sizeof(t_path));
			new_nameless_var->current = *to_inspect;
			new_nameless_var->entered_on_2 = (dict_mod("get", new_link, 0) == 2);
			new_nameless_var->path = new_path;
			q_add(to_search, ft_lstnew(&new_nameless_var, sizeof(new_nameless_var)));
			veccat(to_free, &new_link, sizeof(char *));
			(*to_inspect)->visited |= NOW;
		}
		else if ((*to_inspect)->typ == mid && ((*to_inspect)->visited & NOW) == 0)
		{
			if (dict_mod("get", new_link, 0) == 2)
			{
				new_path = vecnew(found->path->e, found->path->len);
				veccat(new_path, &new_link, sizeof(new_link));
				new_nameless_var = (t_path *)ft_memalloc(sizeof(t_path));
				new_nameless_var->current = *to_inspect;
				new_nameless_var->entered_on_2 = 1;
				new_nameless_var->path = new_path;
				q_add(to_search, ft_lstnew(&new_nameless_var, sizeof(new_nameless_var)));
				veccat(to_free, &new_link, sizeof(char *));
			}
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
	start_info->entered_on_2 = 1;
	while (find_flow(q_new(ft_lstnew(&start_info, sizeof(start_info))), nodes))
		;
}

t_list	*make_list_of(t_npair just_traveled)
{
	t_node	*current;
	t_node	**ln;
	int		i;
	char	*link;
	t_list	*out;

ft_printf("At least we made it in with %p\n", just_traveled);
	current = just_traveled[1];
ft_printf("the node should be at %p\n", current);
ft_printf("The name should be at %p and the links at %p\n", current->name, current->links);
	out = NULL;
	i = 0;
	while ((ln = (t_node **)get_element(current->links,
			sizeof(t_node *), i++)))
	{
ft_printf("We're in the loop!\n");
ft_printf("We're in the loop with %s!\n", (*ln)->name);
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
			ft_printf("%.*sL%s-%s", i, " ", (*nodes)[0]->name, (*nodes)[1]->name);
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

void	send_out(t_npvec *sequence, int num_ants)
{
	t_list	*row;
	int		i;
	t_npair	**whaaat;
	t_list	*oldrow;
	t_queue	*whatever;

	oldrow = NULL;
	whatever = q_new(NULL);
	while (num_ants > 0)
	{
		row = NULL;
		i = 0;
		while ((whaaat = (t_npair **)get_element(sequence, sizeof(t_npair), i)) &&
				i < num_ants)
		{
			ft_lstadd(&row, ft_lstnew(*whaaat, sizeof(t_npair)));
			i++;
		}
		while (oldrow)
		{
			ft_lstadd(&row, make_list_of(*(t_npair *)(oldrow->content)));
			oldrow = oldrow->next;
		}
		q_add(whatever, ft_lstnew(NULL, 0));
		q_add(whatever, row);
		oldrow = row;
		num_ants -= sequence->len / sizeof(t_npair);
	}
	print_and_free(whatever);
}

void	find_path(t_node **nodes, int num_ants)
{
	int		start_ind;
	int		i;
	t_node	**ln;
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
	while ((ln = (t_node **)get_element(nodes[start_ind]->links,
			sizeof(t_node *), i++)))
	{
		link = ft_sthreejoin(nodes[start_ind]->name, "-", (*ln)->name);
		if (dict_mod("get", link, 0) == 0)
			veccat(sequence, &((t_npair){nodes[start_ind], *ln}), sizeof(t_npair));
		free(link);
	}
	while (num_ants > 0)
	{
		send_out(sequence, num_ants);
	}
	free(sequence);
}
