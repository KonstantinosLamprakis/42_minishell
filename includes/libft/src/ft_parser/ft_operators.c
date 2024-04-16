/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:36:49 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 11:25:49 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

int	*get_precedence(void)
{
	static int	precedences[OPERATOR_COUNT];

	precedences[AND] = AND_PRE;
	precedences[OR] = OR_PRE;
	precedences[PIPE] = PIPE_PRE;
	precedences[L_REDIRECT] = L_REDIRECT_PRE;
	precedences[R_REDIRECT] = R_REDIRECT_PRE;
	precedences[L_DELIMITER] = L_DELIMITER_PRE;
	precedences[R_APPEND] = R_APPEND_PRE;
	precedences[L_PARANTHESE] = L_PARANTHESE_PRE;
	precedences[R_PARANTHESE] = R_PARANTHESE_PRE;
	precedences[L_CBRACKET] = L_CBRACKET_PRE;
	precedences[R_CBRACKET] = R_CBRACKET_PRE;
	precedences[L_BRACKET] = L_BRACKET_PRE;
	precedences[R_BRACKET] = R_BRACKET_PRE;
	return (&precedences[0]);
}

char	**get_operators(void)
{
	static char	*operators[OPERATOR_COUNT];

	operators[AND] = AND_OP;
	operators[OR] = OR_OP;
	operators[PIPE] = PIPE_OP;
	operators[L_REDIRECT] = L_REDIRECT_OP;
	operators[R_REDIRECT] = R_REDIRECT_OP;
	operators[L_DELIMITER] = L_DELIMITER_OP;
	operators[R_APPEND] = R_APPEND_OP;
	operators[L_PARANTHESE] = L_PARANTHESE_OP;
	operators[R_PARANTHESE] = R_PARANTHESE_OP;
	operators[L_CBRACKET] = L_CBRACKET_OP;
	operators[R_CBRACKET] = R_CBRACKET_OP;
	operators[L_BRACKET] = L_BRACKET_OP;
	operators[R_BRACKET] = R_BRACKET_OP;
	return (&operators[0]);
}
