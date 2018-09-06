/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlife.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:05:52 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/19 13:06:05 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	return ((char *)ft_memalloc(size + 1));
}

void	ft_strclr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
		*s++ = '\0';
}

void	ft_strdel(char **as)
{
	if (as == NULL)
		return ;
	ft_memdel((void **)as);
}
