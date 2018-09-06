/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 22:26:56 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 22:27:14 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	while (*s != '\0')
		write(1, s++, 1);
}

void	ft_putendl(char const *s)
{
	while (*s != '\0')
		write(1, s++, 1);
	write(1, "\n", 1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n / 10 < 0)
			ft_putnbr(-1 * (n / 10));
		ft_putchar('0' - n % 10);
	}
	else if (n > 0)
	{
		if (n / 10 > 0)
			ft_putnbr(n / 10);
		ft_putchar('0' + n % 10);
	}
	else
		ft_putchar('0');
}
