/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sbtree_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:34:07 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 15:07:24 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

/**
 * @brief Inserts a new node into a sorted binary tree
 *
 * @param root of the sorted binary tree
 * @param item to create the new node
 * @param cmp to keep the binary tree sorted
 */
void	ft_sbtree_insert(t_btree **root, void *item, int (*cmp)(void *, void *))
{
	t_btree	*node;
	t_btree	*last;

	if (!root || !cmp)
		return (set_error((char *)__func__, INVALID_ARG));
	node = ft_btree_create_node(item);
	if (!node)
		return ;
	if (!*root)
	{
		*root = node;
		return ;
	}
	last = ft_sbtree_find_last(*root, item, cmp);
	if (!last)
		return ;
	if ((*cmp)(item, last->item) < 0)
		last->left = node;
	else
		last->right = node;
}
