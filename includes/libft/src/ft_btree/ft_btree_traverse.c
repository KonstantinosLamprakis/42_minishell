/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_traverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:22:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 14:31:25 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_traverse(t_btree *root, void (*f)(void *),
		t_traversal_order order, void (*del)(void *))
{
	if (order == PREFIX)
		ft_btree_iter_prefix(root, f);
	if (order == INFIX)
		ft_btree_iter_infix(root, f);
	if (order == POSTFIX)
		ft_btree_iter_postfix(root, f);
	if (order == BREADTH)
		ft_btree_iter_breadth(root, f, del);
	if (order == DEPTH)
		ft_btree_iter_depth(root, f);
}
