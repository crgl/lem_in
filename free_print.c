/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 13:28:36 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/15 13:28:57 by cgleason         ###   ########.fr       */
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
