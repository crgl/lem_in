/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfresh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:03:31 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/19 13:03:49 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	char	*strim;

	i = 0;
	if (s == NULL)
		return (NULL);
	while ((*s == ' ' || *s == '\t' || *s == '\n') && *s != '\0')
		s++;
	while (s[i] != '\0')
		i++;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\0')
	{
		if (i == 0)
			return (ft_strnew(0));
		i--;
	}
	strim = ft_strnew(i + 1);
	if (strim == NULL)
		return (NULL);
	ft_memset((void *)strim, 32, i + 1);
	i = 0;
	while (strim[i] != '\0')
		strim[i++] = *s++;
	return (strim);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ssub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	ssub = ft_strnew(len);
	if (ssub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ssub[i] = s[(size_t)start + i];
		i++;
	}
	return (ssub);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	s2 = ft_strnew(ft_strlen(s1));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	char	*scat;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	scat = ft_strnew(l1 + l2);
	if (scat == NULL)
		return (NULL);
	while (i < l1)
		scat[i++] = *s1++;
	while (i < l1 + l2)
		scat[i++] = *s2++;
	return (scat);
}
