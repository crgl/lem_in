/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 10:46:43 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/30 10:46:51 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_strtoint	g_colors[9] =
{
	{"black", 0},
	{"red", 1},
	{"green", 2},
	{"yellow", 3},
	{"blue", 4},
	{"magenta", 5},
	{"cyan", 6},
	{"white", 7},
	{NULL, -1},
};

void	cleanup(void)
{
	write(1, "\033[0m", 4);
}

int		color_code(char *color)
{
	int		out;
	int		i;

	out = 0;
	if (color[0] == 'b' && color[1] == '_')
	{
		out = 8;
		color += 2;
	}
	i = 0;
	while (g_colors[i].key != NULL)
	{
		if (ft_strequ(color, g_colors[i].key))
			return (out + g_colors[i].value);
		i++;
	}
	return (-1);
}

int		change_color(const char **fmt, va_list av)
{
	char	*color;

	(*fmt)++;
	color = ft_uimtoa_base(va_arg(av, unsigned int) % 256, 10);
	if (**fmt != 'b' && **fmt != 't')
		return (0);
	write(1, "\033[", 2);
	if (**fmt == 'b')
		write(1, "4", 1);
	else if (**fmt == 't')
		write(1, "3", 1);
	write(1, "8:5:", 4);
	write(1, color, ft_strlen(color));
	free(color);
	write(1, "m", 1);
	*fmt += 2;
	return (0);
}
