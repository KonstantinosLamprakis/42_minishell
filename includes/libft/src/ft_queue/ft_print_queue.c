/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:06:28 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 13:51:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

void	ft_print_queue(t_queue *queue, void (*print_lstnode)(void *))
{
	if (queue->capacity >= 0)
	{
		if (queue->size == 0)
			ft_printf("queue's empty\n  |- capacity = %3d\n", queue->capacity);
		else
			ft_printf("queue's [%-3d / %3d] full\n", queue->size,
				queue->capacity);
	}
	else
	{
		if (queue->size == 0)
			ft_printf("queue's empty\n  |- capacity = infinite\n");
		else
			ft_printf("queue's [%-3d / \236] full\n", queue->size);
	}
	ft_lstiter(*queue->head, print_lstnode);
}
