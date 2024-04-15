/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:25:30 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 14:26:25 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_H
# define FT_QUEUE_H

# include "../ft_error/ft_error.h"
# include "../ft_linked_list/ft_linked_list.h"
# include "../ft_printf/ft_printf.h"

# include <stdlib.h> // malloc, free, NULL

# define INFINITE_CAPACITY -1

typedef struct s_queue
{
	t_list	**head;
	int		capacity;
	int		size;
}			t_queue;

t_queue		*ft_create_queue(int capacity);
void		ft_queue_push(t_queue *queue, void *data);
void		*ft_queue_pop(t_queue *queue, void (*del)(void *));
void		ft_clear_queue(t_queue *queue, void (*del)(void *));
void		ft_print_queue(t_queue *queue, void (*print_lstnode)(void *));

#endif
