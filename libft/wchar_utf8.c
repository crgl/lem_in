/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmanip3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 20:32:11 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/23 20:32:22 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	wchar_to_utf8(char *utf_str, unsigned long long tmp, int *j)
{
	if (tmp >> 16)
	{
		utf_str[*j] = ((tmp >> 18) & 7) | 240;
		utf_str[*j + 1] = ((tmp >> 12) & 63) | 128;
		utf_str[*j + 2] = ((tmp >> 6) & 63) | 128;
		utf_str[*j + 3] = (tmp & 63) | 128;
		*j += 4;
	}
	else if (tmp >> 11)
	{
		utf_str[*j] = ((tmp >> 12) & 15) | 224;
		utf_str[*j + 1] = ((tmp >> 6) & 63) | 128;
		utf_str[*j + 2] = (tmp & 63) | 128;
		*j += 3;
	}
	else if (tmp >> 7)
	{
		utf_str[*j] = ((tmp >> 6) & 31) | 192;
		utf_str[*j + 1] = (tmp & 63) | 128;
		*j += 2;
	}
	else
		utf_str[(*j)++] = tmp & 127;
}

char	*ft_to_utf8(wchar_t *wstr, int wchar_num)
{
	char				utf_str[4 * wchar_num + 1];
	int					i;
	int					j;
	unsigned long long	tmp;
	char				*out;

	i = 0;
	j = 0;
	while (wstr[i])
	{
		tmp = wstr[i++];
		wchar_to_utf8(utf_str, tmp, &j);
	}
	utf_str[j] = '\0';
	out = ft_strdup(utf_str);
	return (out);
}
