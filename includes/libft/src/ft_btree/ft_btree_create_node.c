/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:43:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 11:48:23 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

/**
 * @brief Creates a binary tree node with no left or right child
 *
 * @param item node's item
 * @return t_btree* node
 */
t_btree	*ft_btree_create_node(void *item)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (!node)
		return (set_error((char *)__func__, ALLOC), NULL);
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
