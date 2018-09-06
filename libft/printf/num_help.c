/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 20:32:52 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/25 20:33:00 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

intmax_t	g_sbounds[7][2] = {
	{SCHAR_MIN, SCHAR_MAX},
	{SHRT_MIN, SHRT_MAX},
	{INT_MIN, INT_MAX},
	{LONG_MIN, LONG_MAX},
	{LLONG_MIN, LLONG_MAX},
	{INTMAX_MIN, INTMAX_MAX},
	{-SSIZE_MAX - 1, SSIZE_MAX},
};

uintmax_t	g_ubounds[7][2] = {
	{0, UCHAR_MAX},
	{0, USHRT_MAX},
	{0, UINT_MAX},
	{0, ULONG_MAX},
	{0, ULLONG_MAX},
	{0, UINTMAX_MAX},
	{0, SSIZE_MAX * 2UL + 1UL}
};

char		*prepend(char *bare, char *zeros, char *pre)
{
	char	*tmp;

	tmp = bare;
	bare = ft_strjoin(zeros, bare);
	free(tmp);
	tmp = bare;
	bare = ft_strjoin(pre, bare);
	free(tmp);
	return (bare);
}

void		adjust_sizes(t_sizes *szs, char *pre, char *bare)
{
	if ((szs->opts & PAD_0S) && !(szs->opts & PAD_RT))
	{
		if (*bare)
			szs->width -= ft_strlen(pre);
		if (szs->width > szs->precision)
			szs->precision = szs->width;
		szs->width = 0;
	}
}

uintmax_t	unsgnd_bounds_check(uintmax_t num, t_sizes *szs)
{
	if (szs->length == mxmms)
		return (num);
	while (num > g_ubounds[szs->length][1])
		num -= (g_ubounds[szs->length][1] - g_ubounds[szs->length][0]) + 1;
	while (num < g_ubounds[szs->length][0])
		num += (g_ubounds[szs->length][1] - g_ubounds[szs->length][0]) + 1;
	return (num);
}

intmax_t	sgnd_bounds_check(intmax_t num, t_sizes *szs)
{
	if (szs->length == mxmms)
		return (num);
	while (num > g_sbounds[szs->length][1])
		num -= (g_sbounds[szs->length][1] - g_sbounds[szs->length][0]) + 1;
	while (num < g_sbounds[szs->length][0])
		num += (g_sbounds[szs->length][1] - g_sbounds[szs->length][0]) + 1;
	return (num);
}

char		*clear_0(char *to_print, t_sizes *szs)
{
	if (to_print[0] == '0' && szs->precision == 0)
	{
		free(to_print);
		to_print = ft_strnew(0);
		szs->opts &= ~(PAD_0S | SPC_POS | PLS_POS);
	}
	return (to_print);
}
