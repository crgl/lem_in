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

int		dict_mod(char *op, char *key, int value)
{
	int				ind;
	static char		*keys[DICT_SIZE];
	static t_byte	caps[DICT_SIZE];

	ind = 0;
	if (ft_strequ(op, "set"))
	{
		if (key == NULL)
			freak_out(key);
		ind = index_of(key, DICT_SIZE);
		while (keys[ind])
			ind = (ind + 1) % DICT_SIZE;
		keys[ind] = key;
		caps[ind] = value;
	}
	else if (ft_strequ(op, "mod"))
	{
		if (key == NULL)
			freak_out(key);
		ind = index_of(key, DICT_SIZE);
		while (keys[ind] && ft_strcmp(keys[ind], key))
			ind = (ind + 1) % DICT_SIZE;
		if (keys[ind])
			caps[ind] = value;
		else
			freak_out(key);
	}
	else if (ft_strequ(op, "get"))
	{
		if (key == NULL)
			freak_out(key);
		ind = index_of(key, DICT_SIZE);
		while (keys[ind] && ft_strcmp(keys[ind], key))
			ind = (ind + 1) % DICT_SIZE;
		if (keys[ind])
			return (caps[ind]);
		else
			freak_out(key);
	}
	else if (ft_strequ(op, "clear"))
	{
		while (ind < DICT_SIZE)
			if (keys[ind])
				free(keys[ind++]);
	}
	else
		freak_out(key);
	return (ind);
}
