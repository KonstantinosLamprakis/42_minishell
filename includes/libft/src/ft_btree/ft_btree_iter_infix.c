/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter_infix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:10:33 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 12:14:29 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_iter_infix(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return (set_error((char *)__func__, INVALID_ARG));
	if (root->left)
		ft_btree_iter_infix(root->left, f);
	(*f)(root->item);
	if (root->right)
		ft_btree_iter_infix(root->right, f);
}
