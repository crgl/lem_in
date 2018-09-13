/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:28:53 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/10 12:13:44 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	rot_right(t_splay **root)
{
	t_splay *pivot;

	pivot = (*root)->left;
	(*root)->left = pivot->right;
	if ((*root)->left)
		(*root)->left->parent = (*root);
	pivot->right = (*root);
	(*root)->parent = pivot;
	pivot->pathparent = (*root)->pathparent;
	pivot->parent = NULL;
	(*root) = pivot;
}

void	rot_left(t_splay **root)
{
	t_splay *pivot;

	pivot = (*root)->right;
	(*root)->right = pivot->left;
	if ((*root)->right)
		(*root)->right->parent = (*root);
	pivot->left = (*root);
	(*root)->parent = pivot;
	pivot->pathparent = (*root)->pathparent;
	pivot->parent = NULL;
	(*root) = pivot;
}

void	splay(t_splay *root, int key)
{
	if (!root || root->key == key)
		return (splay);
	if (root->key < key)
	{
		if (!root->left || root->left->key == key)
			return (root);
		if (root->left->key < key)
		{
			return (splay(root->left->left, key));
			rot_right(&root);
		}
		else if (root->left->key > key)
		{
			return (splay(root->left->right, key));
			rot_left(&root);
		}
		if (!root->left)
			return (root);
		else
			return (rot_right(&root));
	}
	else
	{
		if (!root->right || root->left->key == key)
			return (root);
		if (root->right->key > key)
		{
			return (splay(root->right->right, key));
			rot_left(&root);
		}
		else if (root->right->key < key)
		{
			return (splay(root->right->left, key));
			rot_right(&root);
		}
		if (!root->right)
			return (root);
		else
			return (rot_left(&root));
	}
}
