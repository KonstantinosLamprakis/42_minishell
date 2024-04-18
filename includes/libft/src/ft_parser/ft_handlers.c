/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:41:32 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/18 11:03:42 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static void	print_arg(void *arg)
{
	ft_printf("arg: %p\n", arg);
}

t_operator_handler	*get_handlers(void)
{
	static t_operator_handler	handlers[OPERATOR_COUNT];
	int							index;

	index = -1;
	while (++index < OPERATOR_COUNT)
		handlers[index] = print_arg;
	return (&handlers[0]);
}

void	set_handler(t_operators op, t_operator_handler new_handler)
{
	t_operator_handler	*handlers;

	handlers = get_handlers();
	handlers[op] = new_handler;
}
