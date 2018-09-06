/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlife.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:39:06 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/19 12:39:19 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	void	*content_cpy;
	t_list	*new;

	new = (t_list *)ft_memalloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	*new = (t_list){NULL, 0, NULL};
	if (content == NULL)
		return (new);
	content_cpy = ft_memalloc(content_size);
	if (content_cpy == NULL)
		return (NULL);
	ft_memcpy(content_cpy, content, content_size);
	new->content_size = content_size;
	new->content = content_cpy;
	return (new);
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if ((*alst)->next == NULL)
		ft_lstdelone(alst, del);
	else
	{
		del((*alst)->content, (*alst)->content_size);
		ft_lstdel(&((*alst)->next), del);
		free((*alst));
		*alst = NULL;
	}
}
