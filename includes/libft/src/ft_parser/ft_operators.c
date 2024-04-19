/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:36:49 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 13:37:49 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

char	**get_encapsulators(void)
{
	static char	*encapsulators[OPERATOR_COUNT];

	encapsulators[L_PARANTHESE] = L_PARANTHESE_ENC;
	encapsulators[R_PARANTHESE] = R_PARANTHESE_ENC;
	encapsulators[L_CBRACKET] = L_CBRACKET_ENC;
	encapsulators[R_CBRACKET] = R_CBRACKET_ENC;
	encapsulators[L_BRACKET] = L_BRACKET_ENC;
	encapsulators[R_BRACKET] = R_BRACKET_ENC;
	return (&encapsulators[0]);
}

int	*get_lengths(void)
{
	static int	lengths[OPERATOR_COUNT];
	char		**operators;
	int			index;

	operators = get_operators();
	index = -1;
	while (++index < OPERATOR_COUNT)
		lengths[index] = ft_strlen(operators[index]);
	return (&lengths[0]);
}

char	**get_operators(void)
{
	static char	*operators[OPERATOR_COUNT];

	operators[NO_OPERATOR] = "";
	operators[AND] = AND_OP;
	operators[OR] = OR_OP;
	operators[PIPE] = PIPE_OP;
	operators[L_REDIRECT] = L_REDIRECT_OP;
	operators[R_REDIRECT] = R_REDIRECT_OP;
	operators[L_DELIMITER] = L_DELIMITER_OP;
	operators[R_APPEND] = R_APPEND_OP;
	return (&operators[0]);
}
