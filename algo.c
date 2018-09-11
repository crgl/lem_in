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

void	adjust_capacities(t_node **nodes)
{
	return ;
}

void	send_out(t_node **nodes, t_link **sequence, int maximum)
{
	return ;
}

void	find_path(t_node **nodes, t_nodevec *graph, int num_ants)
{
	int		start_ind;
	int		i;
	t_link	*ln;
	t_link	**sequence;

	start_ind = 0;
	while (nodes[start_ind])
	{
		if (nodes[start_ind]->typ == start)
			break ;
		start_ind++;
	}
	if (num_ants < 1)
		return ;
	adjust_capacities(nodes);
	sequence = (t_link **)ft_memalloc(sizeof(t_link *));
	i = 0;
	while ((ln = (t_link *)get_element(nodes[start_ind]->links,
			sizeof(t_link), i++)))
		if (!ln->cap)
			add_to_sequence(ln, sequence);
	while (num_ants > 0)
	{
		send_out(nodes, sequence, num_ants);
		num_ants -= ft_len((void **)sequence);
	}
	free(sequence);
}
