/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casemod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 21:04:49 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/15 16:01:12 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if (c <= (int)'Z' && c >= (int)'A')
		c = 'a' + (c - (int)'A');
	return (c);
}

int		ft_toupper(int c)
{
	if (c <= (int)'z' && c >= (int)'a')
		c = 'A' + (c - (int)'a');
	return (c);
}

void	ft_str_toupper(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		s[i] = ft_toupper(s[i]);
		i++;
	}
}

void	ft_str_tolower(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
}
