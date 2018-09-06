/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstiter_over.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:41:59 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/19 12:42:05 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst == NULL)
		return ;
	else if (lst->next != NULL)
	{
		f(lst);
		ft_lstiter(lst->next, f);
	}
	else
		f(lst);
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;

	if (lst == NULL)
		return (NULL);
	tmp = lst->next;
	lst = f(lst);
	lst->next = ft_lstmap(tmp, f);
	return (lst);
}
