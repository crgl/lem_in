/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dickens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 11:16:13 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/15 11:16:14 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

char	*make_color(t_color color)
{
	char	*r;
	char	*g;
	char	*b;
	char	*out;
	char	*tmp;

	r = ft_itoa((int)((color >> 16) & 0xFF));
	g = ft_itoa((int)((color >> 8) & 0xFF));
	b = ft_itoa((int)((color) & 0xFF));
	tmp = ft_sthreejoin("\033[38;2;", r, ";");
	out = ft_sthreejoin(tmp, g, ";");
	free(tmp);
	tmp = ft_sthreejoin(out, b, "m");
	free(out);
	free(r);
	free(g);
	free(b);
	return (tmp);
}

void	color_change(t_svec *to_print, t_color n_color, t_color *c_color)
{
	char	*ansi;

	ansi = make_color(n_color);
	veccat(to_print, ansi, ft_strlen(ansi) * sizeof(char));
	*c_color = n_color;
	ft_strdel(&ansi);
}

void	check_state(t_ptrmap **annotate, int step, t_color *new_color)
{
	int		i;
	bool	active;

	i = 0;
	active = false;
	while (annotate[i])
	{
		if (annotate[i]->states[step])
		{
			active = true;
			*new_color = annotate[i]->active;
		}
		else if (active == false)
		{
			*new_color = annotate[i]->inactive;
		}
		i++;
	}
}

t_svec	*update_map(char *map, t_ptrmap ***annotate, int step)
{
	t_svec	*to_print;
	t_color	current_color;
	t_color	new_color;
	int		i;

	current_color = EN_INACT;
	new_color = EN_INACT;
	to_print = vecnew("\033[1J", 4 * sizeof(char));
	color_change(to_print, new_color, &current_color);
	i = 0;
	while (map[i])
	{
		if (annotate[i] == NULL)
			veccat(to_print, map + i, sizeof(char));
		else
		{
			check_state(annotate[i], step, &new_color);
			if (new_color != current_color)
				color_change(to_print, new_color, &current_color);
			veccat(to_print, map + i, sizeof(char));
		}
		i++;
	}
	return (to_print);
}

void	print_the_dickens(char *map, t_ptrmap ***annotate, int num_steps)
{
	int		step;
	t_svec	*to_print;
	char	*ansi;

	step = 0;
	while (step < num_steps)
	{
		to_print = update_map(map, annotate, step);
		ansi = vec2str(to_print);
		ft_putstr(ansi);
		usleep(300000);
		ft_strdel(&ansi);
		vecdel(&to_print);
		step++;
	}
}
