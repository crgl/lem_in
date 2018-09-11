/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkcut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:30:50 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/11 14:31:46 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	access(t_splay *node)
{
	splay(node);
	while (node->pathparent)
	{
		splay(node->pathparent);
		node->parent = node->pathparent;
		node->pathparent->right->pathparent = node->pathparent;
		node->pathparent->right->parent = NULL;
		node->pathparent->right = node;
		splay(node);
	}
}

t_splay	*find_root(t_splay *node)
{
	access(node);
	while (node->left)
		node = node->left;
	return (node);
}

void	cut(t_splay *node)
{
	access(node);
	if (node->left)
	{
		node->left->parent = NULL;
		node->left->pathparent = node;
	}
	node->left = NULL;
}

void	link(t_splay *root, t_splay *node)
{
	access(root);
	access(node);
	root->left = node;
	node->parent = root;
}
