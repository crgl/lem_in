/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:04:03 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/20 15:04:05 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	nput_sgnd_dec(va_list av, t_sizes *szs)
{
	char		*to_print;
	intmax_t	num;
	int			i;

	if ((szs->opts & PAD_0S) && (szs->opts & PREC))
		szs->opts ^= PAD_0S;
	if (!(szs->opts & LEN))
		szs->length = ints;
	num = (szs->length <= ints) ? va_arg(av, int) : va_arg(av, intmax_t);
	num = sgnd_bounds_check(num, szs);
	to_print = ft_imtoa(num);
	to_print = clear_0(to_print, szs);
	if (to_print[0] == '-' || (szs->opts & (SPC_POS | PLS_POS)))
		adjust_sizes(szs, "-", to_print);
	else
		adjust_sizes(szs, "", to_print);
	to_print = fluff_int(to_print, szs);
	i = 0;
	if (!(szs->precision) && to_print[0] == '0')
		return (0);
	while (to_print[i])
		i++;
	write(1, to_print, i);
	free(to_print);
	return (i);
}

int	nput_unsgnd_dec(va_list av, t_sizes *szs)
{
	char			*to_print;
	uintmax_t		num;
	int				i;

	if ((szs->opts & PAD_0S) && (szs->opts & PREC))
		szs->opts ^= PAD_0S;
	num = va_arg(av, uintmax_t);
	if (!(szs->opts & LEN))
		szs->length = ints;
	num = unsgnd_bounds_check(num, szs);
	to_print = ft_uimtoa_base(num, 10);
	to_print = clear_0(to_print, szs);
	adjust_sizes(szs, "", to_print);
	to_print = fluff_uint(to_print, szs, "");
	i = 0;
	if (!(szs->precision) && to_print[0] == '0')
		return (0);
	while (to_print[i])
		i++;
	write(1, to_print, i);
	free(to_print);
	return (i);
}

int	nput_oct(va_list av, t_sizes *szs)
{
	char			*to_print;
	uintmax_t		num;
	int				i;
	char			*pre;

	if ((szs->opts & PAD_0S) && (szs->opts & PREC))
		szs->opts ^= PAD_0S;
	pre = "";
	num = (uintmax_t)va_arg(av, uintmax_t);
	if (!(szs->opts & LEN))
		szs->length = ints;
	num = unsgnd_bounds_check(num, szs);
	to_print = ft_uimtoa_base(num, 8);
	to_print = clear_0(to_print, szs);
	if ((szs->opts & USE_ALT) && to_print[0] != '0')
		pre = "0";
	adjust_sizes(szs, pre, to_print);
	to_print = fluff_uint(to_print, szs, pre);
	i = 0;
	while (to_print[i])
		i++;
	write(1, to_print, i);
	free(to_print);
	return (i);
}

int	nput_hex_low(va_list av, t_sizes *szs)
{
	char			*to_print;
	uintmax_t		num;
	int				i;
	char			*pre;

	if ((szs->opts & PAD_0S) && (szs->opts & PREC))
		szs->opts ^= PAD_0S;
	pre = "";
	num = (uintmax_t)va_arg(av, uintmax_t);
	if (!(szs->opts & LEN))
		szs->length = ints;
	num = unsgnd_bounds_check(num, szs);
	to_print = ft_uimtoa_base(num, 16);
	to_print = clear_0(to_print, szs);
	if ((szs->opts & USE_ALT) && *to_print && *to_print != '0')
		pre = "0x";
	adjust_sizes(szs, pre, to_print);
	to_print = fluff_uint(to_print, szs, pre);
	i = 0;
	while (to_print[i])
		i++;
	write(1, to_print, i);
	free(to_print);
	return (i);
}

int	nput_hex_up(va_list av, t_sizes *szs)
{
	char			*to_print;
	uintmax_t		num;
	int				i;
	char			*pre;

	if ((szs->opts & PAD_0S) && (szs->opts & PREC))
		szs->opts ^= PAD_0S;
	pre = "";
	num = (uintmax_t)va_arg(av, uintmax_t);
	if (!(szs->opts & LEN))
		szs->length = ints;
	num = unsgnd_bounds_check(num, szs);
	to_print = ft_uimtoa_base(num, 16);
	to_print = clear_0(to_print, szs);
	if ((szs->opts & USE_ALT) && *to_print && *to_print != '0')
		pre = "0X";
	adjust_sizes(szs, pre, to_print);
	to_print = fluff_uint(to_print, szs, pre);
	ft_str_toupper(to_print);
	i = 0;
	while (to_print[i])
		i++;
	write(1, to_print, i);
	free(to_print);
	return (i);
}
