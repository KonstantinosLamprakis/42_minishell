/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:54:08 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 14:28:01 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

/**
 * @brief Frees the linked_list used for the queue and itself.
 *
 * @param queue
 * @param del function to free the data in the linked_list if necessary.
 * Can be NULL if the data is not allocated.
 */
void	ft_clear_queue(t_queue *queue, void (*del)(void *))
{
	if (!queue)
		return (set_error((char *)__func__, INVALID_ARG));
	if (queue->size > 0)
		ft_lstclear(queue->head, del);
	free(queue->head);
	free(queue);
}
