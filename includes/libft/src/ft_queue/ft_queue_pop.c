/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:43:47 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 14:26:11 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

/**
 * @brief Pops the queue to get the next value and rearranges it.
 *
 * @param queue
 * @return void*
 */
void	*ft_queue_pop(t_queue *queue, void (*del)(void *))
{
	t_list	*tmp;
	void	*tmp_content;

	if (!queue)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	if (queue->size == 0)
		return (set_error((char *)__func__, QUEUE_EMPTY), NULL);
	tmp = *queue->head;
	*queue->head = tmp->next;
	queue->size--;
	tmp_content = tmp->content;
	return ((*del)(tmp), tmp_content);
}
