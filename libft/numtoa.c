/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numtoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:39:51 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/19 14:39:53 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uimtoa_base(uintmax_t n, int base)
{
	char				strn[8 * sizeof(uintmax_t) + 1];
	size_t				i;
	uintmax_t			pow;
	char				*out;
	char				*hex;

	hex = "0123456789abcdef";
	i = 0;
	if (n == 0)
		return (ft_memset(ft_strnew(1), '0', 1));
	pow = 1;
	while (pow <= n / base)
		pow *= base;
	while (pow != 0)
	{
		strn[i++] = hex[n / pow];
		n %= pow;
		pow /= base;
	}
	strn[i] = '\0';
	out = ft_strdup(strn);
	return (out);
}

char	*ft_imtoa(intmax_t n)
{
	char		strn[sizeof(intmax_t) * 3 + 2];
	size_t		i;
	intmax_t	pow;
	char		*out;

	i = 0;
	if (n < 0)
		strn[i++] = '-';
	else if (n > 0)
		n *= -1;
	else
		return (ft_memset(ft_strnew(1), '0', 1));
	pow = -1;
	while (pow >= n / 10)
		pow *= 10;
	while (pow != 0)
	{
		strn[i++] = '0' + n / pow;
		n %= pow;
		pow /= 10;
	}
	strn[i] = '\0';
	out = ft_strdup(strn);
	return (out);
}

char	*ft_ulltoa_base(unsigned long long n, int base)
{
	char				strn[80];
	size_t				i;
	unsigned long long	pow;
	char				*out;
	char				*hex;

	hex = "0123456789abcdef";
	i = 0;
	if (n == 0)
		return (ft_memset(ft_strnew(1), '0', 1));
	pow = 1;
	while (pow >= n / base)
		pow *= base;
	while (pow != 0)
	{
		strn[i++] = hex[n / pow];
		n %= pow;
		pow /= base;
	}
	strn[i] = '\0';
	out = ft_strdup(strn);
	return (out);
}

char	*ft_lltoa(long long n)
{
	char	strn[24];
	size_t	i;
	int		pow;
	char	*out;

	i = 0;
	if (n < 0)
		strn[i++] = '-';
	else if (n > 0)
		n *= -1;
	else
		return (ft_memset(ft_strnew(1), '0', 1));
	pow = -1;
	while (pow >= n / 10)
		pow *= 10;
	while (pow != 0)
	{
		strn[i++] = '0' + n / pow;
		n %= pow;
		pow /= 10;
	}
	strn[i] = '\0';
	out = ft_strdup(strn);
	return (out);
}

char	*ft_itoa(int n)
{
	char	strn[12];
	size_t	i;
	int		pow;
	char	*out;

	i = 0;
	if (n < 0)
		strn[i++] = '-';
	else if (n > 0)
		n *= -1;
	else
		return (ft_memset(ft_strnew(1), '0', 1));
	pow = -1;
	while (pow >= n / 10)
		pow *= 10;
	while (pow != 0)
	{
		strn[i++] = '0' + n / pow;
		n %= pow;
		pow /= 10;
	}
	strn[i] = '\0';
	out = ft_strdup(strn);
	return (out);
}
