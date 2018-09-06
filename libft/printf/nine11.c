/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nine11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 20:11:03 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/26 20:53:39 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_dispatch	g_dsp[12] = {
	{&nput_string, "s", ALL},
	{&nput_wstring, "S", ALL},
	{&nput_pointer, "p", ALL | IS_NUM},
	{&nput_sgnd_dec, "dDi", ALL | IS_NUM | IS_SGND},
	{&nput_oct, "oO", HAS_ALT | ALL | IS_NUM},
	{&nput_unsgnd_dec, "uU", ALL | IS_NUM},
	{&nput_hex_low, "x", HAS_ALT | ALL | IS_NUM},
	{&nput_hex_up, "X", HAS_ALT | ALL | IS_NUM},
	{&nput_char, "c", ALL},
	{&nput_wchar, "C", ALL},
	{&nput_percent, "%", ALL},
	{NULL, "", 0}
};

void	fill_sizes(const char **fmt, t_sizes *szs, char *args, va_list av)
{
	int	ind;

	ind = chrind(args, **fmt);
	while (ind > -1)
	{
		if (ind >= min_width)
		{
			szs->width = find_min_width(fmt, av, szs);
			ind = min_width;
		}
		else if (ind == precise)
			szs->precision = find_precision(fmt, av);
		szs->opts |= 1 << ind;
		(*fmt)++;
		ind = chrind(args, **fmt);
	}
	if (**fmt == 'h' || **fmt == 'l' || **fmt == 'j' || **fmt == 'z')
	{
		szs->length = find_length(fmt);
		(*fmt)++;
		szs->opts |= 128;
	}
	while (**fmt == 'h' || **fmt == 'l' || **fmt == 'j' || **fmt == 'z')
		(*fmt)++;
}

int		print_arg(const char **fmt, va_list av, t_sizes *szs)
{
	int	ind;
	int	out;
	int	cap;

	ind = 0;
	while (g_dsp[ind].put != NULL)
	{
		if ((cap = chrind(g_dsp[ind].chrs, **fmt)) != -1)
		{
			szs->opts &= g_dsp[ind].flags;
			if ((**fmt == 's' || **fmt == 'c') && *(*fmt - 1) == 'l')
				ind++;
			if (cap == 1)
			{
				szs->opts |= 128;
				szs->length = longs;
			}
			out = g_dsp[ind].put(av, szs);
			(*fmt)++;
			return (out);
		}
		ind++;
	}
	return (0);
}
