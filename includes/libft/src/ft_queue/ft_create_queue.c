/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:27:13 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 13:41:55 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

t_queue	*ft_create_queue(int capacity)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
		return (set_error((char *)__func__, ALLOC), NULL);
	queue->capacity = capacity;
	queue->head = malloc(sizeof(t_list *));
	if (!queue->head)
		return (set_error((char *)__func__, ALLOC), NULL);
	queue->size = 0;
	return (queue);
}
