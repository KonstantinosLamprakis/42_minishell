/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter_depth.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:29:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 14:31:07 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

/**
 * @brief Depth-first search
 *
 * @param root
 * @param f function to apply to each node
 */
void	ft_btree_iter_depth(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return (set_error((char *)__func__, INVALID_ARG));
	(*f)(root->item);
	if (root->left)
		ft_btree_iter_depth(root->left, f);
	if (root->right)
		ft_btree_iter_depth(root->right, f);
}
