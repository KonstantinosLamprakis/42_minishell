/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_found.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:46:43 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 12:42:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_found_encapsulator(t_token *token, char *str, int start,
		t_encapsulators enc)
{
	token->start = start;
	token->enc = enc;
	token->op = -1;
	if (enc == L_PARANTHESE)
		token->end = token->start + endof_paranthese(str, start);
	if (*get_errno() != NO_ERROR)
		return (0);
	return (1);
}

int	handle_found_operator(t_token *token, int index, t_operators op)
{
	token->op = op;
	token->enc = -1;
	token->start = index;
	save_next_token(token->str, token);
	if (*get_errno() != NO_ERROR)
		return (0);
	return (1);
}
