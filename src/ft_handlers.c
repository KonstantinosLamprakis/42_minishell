/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:41:32 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 13:37:19 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_operator_handler	*get_handlers(void)
{
	static t_operator_handler	handlers[OPERATOR_COUNT + 2] = {0};

	return (&handlers[0]);
}

void	set_handler(t_operators op, t_operator_handler new_handler)
{
	t_operator_handler	*handlers;

	handlers = get_handlers();
	handlers[op] = new_handler;
}
