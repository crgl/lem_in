/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmanip2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 20:00:42 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/20 20:00:50 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrlen(const wchar_t *s)
{
	size_t	i;

	i = 0;
	while (*s++ != 0)
		i++;
	return (i);
}

wchar_t	*ft_wstrnew(size_t size)
{
	return ((wchar_t *)ft_memalloc((size + 1) * sizeof(wchar_t)));
}

wchar_t	*ft_wstrdup(wchar_t *s)
{
	wchar_t	*snew;
	size_t	i;

	if (s == NULL)
		return (NULL);
	snew = ft_wstrnew(ft_wstrlen(s));
	if (snew == NULL)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		snew[i] = s[i];
		i++;
	}
	snew[i] = 0;
	return (snew);
}

wchar_t	*ft_wstrjoin(wchar_t const *s1, wchar_t const *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	wchar_t	*scat;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	l1 = ft_wstrlen(s1);
	l2 = ft_wstrlen(s2);
	scat = ft_wstrnew(l1 + l2);
	if (scat == NULL)
		return (NULL);
	while (i < l1)
		scat[i++] = *s1++;
	while (i < l1 + l2)
		scat[i++] = *s2++;
	return (scat);
}
