/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter_postfix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:10:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 12:18:52 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_iter_postfix(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return (set_error((char *)__func__, INVALID_ARG));
	if (root->right)
		ft_btree_iter_postfix(root->right, f);
	if (root->left)
		ft_btree_iter_postfix(root->left, f);
	(*f)(root->item);
}
