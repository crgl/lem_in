/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   striter_over.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 22:30:31 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 22:30:47 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	if (s == NULL || f == NULL)
		return ;
	while (*s != '\0')
		f(s++);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*snew;
	int		i;

	if (s == NULL)
		return (NULL);
	snew = ft_strnew(ft_strlen(s));
	if (snew == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
		snew[i++] = f(*s++);
	return (snew);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*snew;

	if (s == NULL)
		return (NULL);
	snew = ft_strnew(ft_strlen(s));
	if (snew == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		snew[i] = f(i, s[i]);
		i++;
	}
	return (snew);
}
