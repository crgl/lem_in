/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 20:05:23 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 20:05:50 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	*vecnew(void const *content, size_t content_size)
{
	size_t	i;
	t_vec	*newvec;

	i = 1;
	while (i <= content_size)
		i *= 2;
	newvec = (t_vec *)ft_memalloc(sizeof(t_vec));
	if (newvec == NULL)
		return (NULL);
	newvec->e = ft_memalloc(i);
	if (newvec->e == NULL)
	{
		free(newvec);
		return (NULL);
	}
	if (content)
	{
		ft_memcpy(newvec->e, content, content_size);
		newvec->len = content_size;
	}
	else
		newvec->len = 0;
	newvec->cap = i;
	return (newvec);
}

t_vec	*str2vec(char *str)
{
	return (vecnew((void *)str, ft_strlen(str)));
}

int		veccat(t_vec *vec, void const *content, size_t content_size)
{
	void	*tmp;

	while (vec->len + content_size >= vec->cap)
	{
		tmp = ft_memalloc(vec->cap * 2);
		if (tmp == NULL)
			return (-1);
		ft_memcpy(tmp, vec->e, vec->len);
		free(vec->e);
		vec->e = tmp;
		vec->cap *= 2;
	}
	ft_memcpy(vec->e + vec->len, content, content_size);
	vec->len += content_size;
	return (0);
}

char	*vec2str(t_vec *vec)
{
	char	*output;

	output = (char *)ft_strnew(vec->len);
	if (output == NULL)
		return (NULL);
	ft_memcpy(output, vec->e, vec->len);
	return (output);
}

void	vecdel(t_vec **avec)
{
	free((*avec)->e);
	free(*avec);
	*avec = NULL;
}
