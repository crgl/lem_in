/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:36:29 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/15 18:36:34 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

char	*inspect_link(t_node **nodes, t_queue *to_search, t_path *found,
			t_node *to_inspect)
{
	int		i;
	char	**link;
	char	*new_link;

	new_link = ft_sthreejoin(found->current->name, "-", to_inspect->name);
	if (dict_mod("get", new_link, 0) != 0)
	{
		if (to_inspect->typ == end)
		{
			i = 0;
			while ((link = (char **)get_element(found->path,
										sizeof(char *), i++)))
				traverse(*link, nodes);
			traverse(new_link, nodes);
			free(new_link);
			return (NULL);
		}
		else if (AVAIL(to_inspect) && (UNRESTRICTED(found) || REV(new_link)))
		{
			add_node_to_queue(new_link, found, to_inspect, to_search);
			if (dict_mod("get", new_link, 0) == 2 || OFF_PATH(to_inspect))
				to_inspect->visited |= NOW;
		}
	}
	return (new_link);
}

t_path	*get_current_path(t_queue *to_search, t_svec **to_free)
{
	t_list	*next_node;
	t_path	*found;

	if (to_search->start == NULL)
		return (NULL);
	if (!*to_free)
		*to_free = vecnew(NULL, sizeof(char *));
	next_node = q_pop(to_search);
	found = *((t_path **)(next_node->content));
	free(next_node->content);
	free(next_node);
	return (found);
}

void	free_path(t_path *path)
{
	if (path && path->current->typ != start)
	{
		vecdel(&(path->path));
		free(path);
	}
}

int		find_flow(t_queue *to_search, t_node **nodes, size_t i)
{
	static t_svec	*to_free;
	t_path			*found;
	t_node			**to_inspect;
	char			*new_link;

	if ((found = get_current_path(to_search, &to_free)) == NULL)
	{
		search_and_destroy(to_search, found, to_free);
		vecdel(&to_free);
		return (0);
	}
	while ((to_inspect = (t_node **)get_element(found->current->links,
										sizeof(t_node *), i++)))
	{
		if ((new_link = inspect_link(nodes, to_search, found,
							*to_inspect)) == NULL)
		{
			search_and_destroy(to_search, found, to_free);
			vecdel(&to_free);
			return (1);
		}
		veccat(to_free, &new_link, sizeof(char *));
	}
	free_path(found);
	return (find_flow(to_search, nodes, 0));
}
