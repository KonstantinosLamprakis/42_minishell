/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_found.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:46:43 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 09:59:43 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

int	handle_found_encapsulator(t_token *token, char *str, int start,
		t_encapsulators enc)
{
	token->start = start;
	token->enc = enc;
	token->op = -1;
	if (enc == L_PARANTHESE)
		token->end = token->start + endof_paranthese(str, start);
	return (1);
}

int	handle_found_operator(t_token *token, int index, t_operators op)
{
	token->op = op;
	token->enc = -1;
	token->start = index;
	return (1);
}
