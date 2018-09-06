/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:21:56 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/09 22:21:09 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	flag;
	int	num;

	flag = -1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		flag = (*str++ == '-') ? 1 : -1;
	while (*str >= '0' && *str <= '9')
		num = num * 10 - (*str++ - '0');
	num *= flag;
	return (num);
}
