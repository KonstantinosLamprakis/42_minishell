/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter_breadth.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:47:30 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 14:28:19 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

/**
 * @brief Breadth-first search
 *
 * @param root
 * @param f function to apply to each node
 * @param del function to delete a btree node
 */
void	ft_btree_iter_breadth(t_btree *root, void (*f)(void *),
		void (*del)(void *))
{
	t_queue	*queue;
	t_btree	*node;

	queue = ft_create_queue(INFINITE_CAPACITY);
	if (!queue)
		return (set_error((char *)__func__, ALLOC));
	ft_queue_push(queue, (void *)root);
	while (queue->size > 0)
	{
		node = ft_queue_pop(queue, del);
		if (!node)
			return (ft_clear_queue(queue, del));
		(*f)(node->item);
		if (node->left)
			ft_queue_push(queue, node->left);
		if (node->right)
			ft_queue_push(queue, node->right);
	}
	ft_clear_queue(queue, del);
}
