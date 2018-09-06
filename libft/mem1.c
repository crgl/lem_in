/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 20:01:32 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 20:01:57 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*res;
	size_t	i;

	i = 0;
	res = malloc(size);
	if (res == NULL)
		return (res);
	while (i < size)
		*((unsigned char *)res + i++) = (unsigned char)0;
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*((unsigned char *)s + i++) = (unsigned char)0;
}

void	*ft_memset(void *ptr, int stpd, size_t n)
{
	unsigned char	c;
	size_t			i;

	c = (unsigned char)stpd;
	i = 0;
	while (i < n)
		*((unsigned char *)ptr + i++) = c;
	return (ptr);
}

void	ft_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)((unsigned char *)s + i));
		i++;
	}
	return (NULL);
}
