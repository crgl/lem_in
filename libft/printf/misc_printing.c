/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_printing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 20:25:58 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/25 20:26:10 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	nput_percent(va_list av, t_sizes *sizes)
{
	char	*to_p;
	int		i;

	(void)av;
	to_p = ft_memalloc(sizeof(char) * 2);
	to_p[0] = '%';
	if (sizes->precision || sizes->width)
		to_p = fluff_string(to_p, sizes);
	i = 0;
	while (to_p[i])
		i++;
	write(1, to_p, i);
	free(to_p);
	return (i);
}

int	nput_pointer(va_list av, t_sizes *sizes)
{
	char				*to_p;
	uintmax_t			num;
	int					i;

	if ((sizes->opts & PAD_0S) && (sizes->opts & PREC))
		sizes->opts ^= PAD_0S;
	num = (uintmax_t)(va_arg(av, void *) - (void *)0);
	to_p = ft_uimtoa_base(num, 16);
	to_p = clear_0(to_p, sizes);
	adjust_sizes(sizes, "0x", to_p);
	to_p = fluff_uint(to_p, sizes, "0x");
	i = 0;
	while (to_p[i])
		i++;
	write(1, to_p, i);
	free(to_p);
	return (i);
}
