/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:52:11 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/10 19:16:42 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_content(char **sarray, size_t ct)
{
	if (ct == 0)
		return ;
	while (--ct)
		free(sarray[ct]);
	free(sarray[ct]);
}

static char	**lcl_strbits(char *dst, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			dst[i] = s[i];
			i++;
		}
		j++;
	}
	return ((char **)malloc((j + 1) * sizeof(char *)));
}

static int	lcl_strarray(char **output, char *temp, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		output[j] = ft_strdup(temp + i);
		if (output[j] == NULL)
		{
			free_content(output, j);
			return (1);
		}
		while (s[i] != c && s[i] != '\0')
			i++;
		j++;
	}
	output[j] = NULL;
	return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**output;
	char	*temp;

	if (s == NULL)
		return (NULL);
	temp = ft_strnew(ft_strlen(s) + 1);
	if (temp == NULL)
		return (NULL);
	output = lcl_strbits(temp, s, c);
	if (output == NULL)
		return (NULL);
	if (lcl_strarray(output, temp, s, c) != 0)
	{
		free(temp);
		free(output);
		return (NULL);
	}
	free(temp);
	return (output);
}
