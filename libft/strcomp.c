/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcomp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:50:16 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/19 12:50:34 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == s2)
			return (1);
		return (0);
	}
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == s2)
			return (1);
		return (0);
	}
	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	return ((int)((unsigned char)(*s1) - (unsigned char)(*s2)));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((int)((unsigned char)(s1[i]) - (unsigned char)(s2[i])));
}
