/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 21:48:20 by tdiaz             #+#    #+#             */
/*   Updated: 2018/09/13 21:48:26 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdbool.h>
# include <limits.h>
# include "libft/libft.h"

# define E_INACT 0x00aa0000
# define E_ACT 0x00ff0055
# define SN_INACT 0x00aaaaaa
# define SN_ACT 0x00ffffff
# define MN_INACT 0x0000aa00
# define MN_ACT 0x0055ff00
# define EN_INACT 0x000000aa
# define EN_ACT 0x000011ff
# define LL long long

typedef unsigned int	t_color;
typedef int				t_pair[2];
typedef t_vec			t_svec;

typedef struct	s_ptrmap
{
	t_color			inactive;
	t_color			active;
	t_pair			coords[3];
	char			*names[3];
	bool			*states;
}				t_ptrmap;

typedef t_vec			t_pmvec;

#endif
