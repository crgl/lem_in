/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qops.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz    <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 19:34:29 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/11 19:34:41 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

t_queue	*q_new(t_list *list)
{
	t_queue *queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->start = list;
	while (list && list->next)
		list = list->next;
	queue->end = list;
	return (queue);
}

void	q_add(t_queue *queue, t_list *list)
{
	if (!queue || !list)
		return ;
	if (queue->end)
		queue->end->next = list;
	else
		queue->start = list;
	while (list->next)
		list = list->next;
	queue->end = list;
}

t_list	*q_pop(t_queue *queue)
{
	t_list	*out;

	if (!queue || !queue->start)
		return (NULL);
	out = queue->start;
	if (out)
		queue->start = out->next;
	if (queue->start == NULL)
		queue->end = NULL;
	return (out);
}
