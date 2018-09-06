/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stuff_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 22:27:23 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 22:27:38 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	while (*s != '\0')
		write(fd, s++, 1);
}

void	ft_putendl_fd(char const *s, int fd)
{
	while (*s != '\0')
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n / 10 < 0)
			ft_putnbr_fd(-1 * (n / 10), fd);
		ft_putchar_fd('0' - n % 10, fd);
	}
	else if (n > 0)
	{
		if (n / 10 > 0)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd('0' + n % 10, fd);
	}
	else
		ft_putchar_fd('0', fd);
}
