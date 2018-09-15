/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_specific.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:27:33 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/15 09:27:39 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_matrix(void ***twod)
{
	int	i;

	i = 0;
	if (*twod == NULL)
		return ;
	while ((*twod)[i] != NULL)
		free((*twod)[i++]);
	free(*twod);
	*twod = NULL;
}

char	*ft_sthreejoin(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*out;

	tmp = ft_strjoin(s1, s2);
	out = ft_strjoin(tmp, s3);
	if (tmp)
		free(tmp);
	return (out);
}
