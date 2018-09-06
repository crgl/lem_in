/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 13:57:28 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 13:57:47 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	add_preface(char *bare, t_sizes *sizes, char *zeros)
{
	int		curr_len;
	int		i;

	curr_len = ft_strlen(bare);
	i = 1;
	if (bare[0] == '-' && curr_len - 1 < sizes->precision)
	{
		bare[0] = '0';
		zeros[0] = '-';
	}
	else if (sizes->opts & PLS_POS && bare[0] != '-')
		zeros[0] = '+';
	else if (sizes->opts & SPC_POS && bare[0] != '-')
		zeros[0] = ' ';
	else
		i--;
	if (curr_len < sizes->precision)
	{
		ft_memset(zeros + i, '0', sizes->precision - curr_len);
		zeros[sizes->precision - curr_len + i] = '\0';
	}
	else
		zeros[i] = '\0';
}

char	*fluff_int(char *bare, t_sizes *sizes)
{
	char	zeros[sizes->precision + 2];
	char	spaces[sizes->width];
	int		curr_len;
	char	*tmp;

	zeros[0] = '\0';
	add_preface(bare, sizes, zeros);
	tmp = bare;
	bare = ft_strjoin(zeros, bare);
	free(tmp);
	curr_len = ft_strlen(bare);
	if (curr_len < sizes->width)
	{
		ft_memset(spaces, ' ', sizes->width - curr_len);
		spaces[sizes->width - curr_len] = '\0';
		tmp = bare;
		if (sizes->opts & PAD_RT)
			bare = ft_strjoin(bare, spaces);
		else
			bare = ft_strjoin(spaces, bare);
		free(tmp);
	}
	return (bare);
}

char	*fluff_uint(char *bare, t_sizes *sizes, char *pre)
{
	char	zeros[sizes->precision + 1];
	char	spcs[sizes->width];
	int		curr_len;
	int		i;
	char	*tmp;

	curr_len = ft_strlen(bare);
	i = 0;
	if (curr_len < sizes->precision && ft_strequ(pre, "0")
			&& !(sizes->opts & PAD_0S))
		pre = "";
	while (i < sizes->precision - curr_len)
		zeros[i++] = '0';
	zeros[i] = '\0';
	bare = prepend(bare, zeros, pre);
	curr_len = ft_strlen(bare);
	if (curr_len >= sizes->width)
		return (bare);
	ft_memset(spcs, ' ', sizes->width - curr_len);
	spcs[sizes->width - curr_len] = '\0';
	tmp = bare;
	bare = (sizes->opts & PAD_RT) ? ft_strjoin(bare, spcs)
		: ft_strjoin(spcs, bare);
	free(tmp);
	return (bare);
}

char	*fluff_string(char *bare, t_sizes *sizes)
{
	char	spaces[sizes->width];
	char	*tmp;

	spaces[0] = '\0';
	if ((sizes->opts & PREC) && ft_strlen(bare) > (size_t)sizes->precision)
		bare[sizes->precision] = '\0';
	if (ft_strlen(bare) < (size_t)sizes->width)
	{
		ft_memset(spaces, ' ', sizes->width - ft_strlen(bare));
		spaces[sizes->width - ft_strlen(bare)] = '\0';
	}
	tmp = bare;
	if (sizes->opts & PAD_RT)
		bare = ft_strjoin(bare, spaces);
	else
		bare = ft_strjoin(spaces, bare);
	free(tmp);
	return (bare);
}

wchar_t	*fluff_wstring(wchar_t *bare, t_sizes *sizes)
{
	wchar_t	spaces[sizes->width];
	wchar_t	*tmp;
	int		len;

	spaces[0] = 0;
	if ((sizes->opts & PREC) && ft_wstrlen(bare) > (size_t)sizes->precision)
		bare[sizes->precision] = 0;
	len = ft_wstrlen(bare);
	if (len < sizes->width)
		spaces[sizes->width - len] = 0;
	while (++len <= sizes->width)
		spaces[sizes->width - len] = L' ';
	tmp = bare;
	if (sizes->opts & PAD_RT)
		bare = ft_wstrjoin(bare, spaces);
	else
		bare = ft_wstrjoin(spaces, bare);
	free(tmp);
	return (bare);
}
