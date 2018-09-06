/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:49:51 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/19 12:50:05 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		chrind(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s != '\0')
		s++;
	if ((char)c == '\0' || *s != '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(s + res));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			res = i;
		i++;
	}
	if (s[res] == '\0')
		return (NULL);
	return ((char *)(s + res));
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		i = 0;
		while (haystack[i] == needle[i] && haystack[i] != '\0')
			i++;
		if (needle[i] == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0')
			j++;
		if (needle[j] == '\0' && i + j <= n)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
