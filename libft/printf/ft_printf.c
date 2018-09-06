/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 19:07:15 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 13:26:36 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		find_min_width(const char **fmt, va_list av, t_sizes *sizes)
{
	int	num;

	num = 0;
	if (**fmt == '*')
	{
		num = va_arg(av, int);
		if (num < 0)
		{
			num *= -1;
			sizes->opts |= PAD_RT;
		}
		return (num);
	}
	while (**fmt >= '0' && **fmt <= '9')
	{
		num = num * 10 + (**fmt - '0');
		(*fmt)++;
	}
	(*fmt)--;
	return (num);
}

int		find_precision(const char **fmt, va_list av)
{
	int	flag;
	int	num;

	flag = 1;
	num = 0;
	(*fmt)++;
	if (**fmt == '-' || **fmt == '+')
	{
		flag = (**fmt == '-') ? -1 : 1;
		(*fmt)++;
	}
	if (**fmt == '*' && *(*fmt - 1) == '.')
		num = va_arg(av, int);
	else
	{
		while (**fmt >= '0' && **fmt <= '9')
		{
			num = num * 10 + (**fmt - '0');
			(*fmt)++;
		}
		(*fmt)--;
	}
	num = (num * flag < 0) ? 0 : num * flag;
	return (num);
}

size_t	find_length(const char **fmt)
{
	if (**fmt == 'z')
		return (szts);
	if (**fmt == 'h')
	{
		if (*(*fmt + 1) == 'h')
		{
			(*fmt)++;
			return (chrs);
		}
		return (shrts);
	}
	if (**fmt == 'l')
	{
		if (*(*fmt + 1) == 'l')
		{
			(*fmt)++;
			return (llongs);
		}
		return (longs);
	}
	if (**fmt == 'j')
		return (mxmms);
	return (0);
}

int		dispatch(const char **fmt, va_list av)
{
	char	*args;
	t_sizes	*sizes;
	int		out;

	args = "#0- +.123456789*";
	sizes = (t_sizes *)malloc(sizeof(t_sizes));
	if (!sizes)
		return (-1);
	*sizes = (t_sizes){0, 0, 1, 0};
	(*fmt)++;
	fill_sizes(fmt, sizes, args, av);
	if (sizes->opts & PAD_RT)
		sizes->opts &= ~PAD_0S;
	if (**fmt == '{')
		out = change_color(fmt, av);
	else
		out = print_arg(fmt, av, sizes);
	free(sizes);
	return (out);
}

int		ft_printf(const char *fmt, ...)
{
	va_list	av;
	int		i;
	int		out;
	int		tmp;

	va_start(av, fmt);
	out = 0;
	while (*fmt && out != -1)
	{
		i = 0;
		while (fmt[i] && fmt[i] != '%')
			i++;
		write(1, fmt, i);
		fmt += i;
		out += i;
		if (*fmt == '%')
		{
			tmp = dispatch(&fmt, av) + out;
			tmp = (tmp - out == -1) ? -1 : tmp;
			out = tmp;
		}
	}
	va_end(av);
	return (out);
}
