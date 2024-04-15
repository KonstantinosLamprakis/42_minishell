/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter_prefix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:50:59 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 12:14:23 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_iter_prefix(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return (set_error((char *)__func__, INVALID_ARG));
	(*f)(root->item);
	if (root->left)
		ft_btree_iter_prefix(root->left, f);
	if (root->right)
		ft_btree_iter_prefix(root->right, f);
}
