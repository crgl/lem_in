/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:40:50 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/19 17:40:57 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	heap_repair(void **array, int ind, int n, t_cmp cmp)
{
	int			lind;
	int			rind;
	int			maxind;
	void		*tmp;

	lind = 2 * ind + 1;
	rind = 2 * ind + 2;
	maxind = ind;
	if (lind < n)
		if (cmp(array[lind], array[maxind]) > 0)
			maxind = lind;
	if (rind < n)
		if (cmp(array[rind], array[maxind]) > 0)
			maxind = rind;
	if (maxind != ind)
	{
		tmp = array[ind];
		array[ind] = array[maxind];
		array[maxind] = tmp;
		heap_repair(array, maxind, n, cmp);
	}
}

void	**vec_sort(t_vec *hvec, size_t sz, t_cmp cmp)
{
	void			**out;
	char			*loc;
	unsigned long	i;
	void			*tmp;

	out = (void **)ft_memalloc((hvec->len / sz + 1) * sizeof(void *));
	loc = (char *)hvec->e;
	i = 0;
	while (i < hvec->len / sz)
	{
		out[i] = (void *)(loc + i * sz);
		i++;
	}
	i = hvec->len / (2 * sz) + 1;
	while (i--)
		heap_repair(out, i, hvec->len / sz, cmp);
	i = hvec->len / sz;
	while (i--)
	{
		tmp = out[i];
		out[i] = out[0];
		out[0] = tmp;
		heap_repair(out, 0, i, cmp);
	}
	return (out);
}
