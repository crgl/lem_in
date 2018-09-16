/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 18:09:59 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/11 18:10:07 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	freak_out(char *key)
{
	ft_printf("BUT YOU PROMISED IT WOULD BE OKAY, %s!\n", key);
	exit(-2147483648);
}

int		dict_clear(char **keys)
{
	int	ind;

	ind = 0;
	while (ind < DICT_SIZE)
		if (keys[ind++])
			free(keys[ind - 1]);
	return (ind);
}

int		dict_mod(char *op, char *key, int value)
{
	int				ind;
	static char		*keys[DICT_SIZE];
	static t_byte	caps[DICT_SIZE];

	if (ft_strequ(op, "clear"))
		return (dict_clear(keys));
	if (key == NULL)
		freak_out(key);
	ind = index_of(key, DICT_SIZE);
	while (keys[ind] && (ft_strequ(op, "set") || ft_strcmp(keys[ind], key)))
		ind = (ind + 1) % DICT_SIZE;
	if (ft_strequ(op, "set"))
	{
		keys[ind] = key;
		caps[ind] = value;
	}
	else if (keys[ind] == NULL)
		freak_out(key);
	else if (ft_strequ(op, "mod"))
		caps[ind] += value;
	else if (ft_strequ(op, "get"))
		return (caps[ind]);
	return (ind);
}
