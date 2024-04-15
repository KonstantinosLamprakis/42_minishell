/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sbtree_find_last.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:02:09 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 15:05:17 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_sbtree_find_last(t_btree *root, void *ref, int (*cmp)(void *,
			void *))
{
	t_btree	*last;
	t_btree	*current;

	if (!root || !cmp)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	last = root;
	if ((*cmp)(ref, last->item) < 0)
		current = last->left;
	else
		current = last->right;
	while (current)
	{
		last = current;
		if ((*cmp)(ref, last->item) < 0)
			current = last->left;
		else
			current = last->right;
	}
	return (last);
}
