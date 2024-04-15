/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:35:48 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 13:51:53 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

/**
 * @brief Push a new element into the queue. Rises an error if at capacity
 *
 * @param queue
 * @param data of the new element in the queue
 */
void	ft_queue_push(t_queue *queue, void *data)
{
	t_list	*elem;

	if (!queue || !data)
		return (set_error((char *)__func__, INVALID_ARG));
	if (queue->capacity >= 0 && queue->size == queue->capacity)
		return (set_error((char *)__func__, QUEUE_AT_CAPACITY));
	elem = ft_lstnew(data);
	if (!elem)
		return (set_error((char *)__func__, ALLOC));
	ft_lstadd_back(queue->head, elem);
	queue->size++;
}
