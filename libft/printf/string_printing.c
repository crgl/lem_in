/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:04:11 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/20 15:04:14 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

#include <stdio.h>

int		nput_char(va_list av, t_sizes *sizes)
{
	char	*to_p;
	int		i;
	int		flag;

	flag = 0;
	to_p = ft_memalloc(sizeof(char) * 2);
	to_p[0] = (char)va_arg(av, int);
	if (to_p[0] == '\0')
		flag = 1;
	to_p = fluff_string(to_p, sizes);
	i = 0;
	while (to_p[i])
		i++;
	if (flag && sizes->precision != 0 && i)
		i--;
	if (flag && sizes->precision != 0 && sizes->opts & PAD_RT)
		write(1, "\0", 1);
	write(1, to_p, i);
	if (flag && sizes->precision != 0 && !(sizes->opts & PAD_RT))
		write(1, "\0", 1);
	free(to_p);
	return (i + flag);
}

int		nput_wchar(va_list av, t_sizes *sizes)
{
	wchar_t			*to_prep;
	int				i;
	int				flag;
	char			*to_print;
	int				wchar_num;

	flag = 0;
	to_prep = ft_memalloc(sizeof(wchar_t) * 2);
	to_prep[0] = va_arg(av, wchar_t);
	if (to_prep[0] == 0)
		flag = 1;
	to_prep = fluff_wstring(to_prep, sizes);
	wchar_num = ft_wstrlen(to_prep);
	to_print = ft_to_utf8(to_prep, wchar_num);
	free(to_prep);
	i = 0;
	while (to_print[i])
		i++;
	write(1, to_print, i);
	if (flag)
		write(1, "\0", 1);
	free(to_print);
	return (wchar_num + flag);
}

int		nput_string(va_list av, t_sizes *sizes)
{
	char	*to_p;
	int		i;

	to_p = va_arg(av, char *);
	if (to_p == NULL)
		to_p = ft_strdup("(null)");
	else
		to_p = ft_strdup(to_p);
	to_p = fluff_string(to_p, sizes);
	i = 0;
	while (to_p[i])
		i++;
	write(1, to_p, i);
	free(to_p);
	return (i);
}

int		nput_wstring(va_list av, t_sizes *sizes)
{
	wchar_t	*to_prep;
	char	*to_print;
	int		i;
	int		wchar_num;

	to_prep = ft_wstrdup(va_arg(av, wchar_t *));
	if (to_prep == NULL)
		to_prep = ft_wstrdup(L"(null)");
	to_prep = fluff_wstring(to_prep, sizes);
	wchar_num = ft_wstrlen(to_prep);
	to_print = ft_to_utf8(to_prep, wchar_num);
	free(to_prep);
	i = 0;
	while (to_print[i])
		i++;
	write(1, to_print, i);
	free(to_print);
	return (wchar_num);
}
