/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:21:20 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 11:47:12 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static int	ft_is_doperator(const char *str, t_operators op)
{
	if (op == AND)
		return (ft_strnstr(str, AND_OP, 2) != NULL);
	if (op == OR)
		return (ft_strnstr(str, OR_OP, 2) != NULL);
	if (op == L_DELIMITER)
		return (ft_strnstr(str, L_DELIMITER_OP, 2) != NULL);
	if (op == R_APPEND)
		return (ft_strnstr(str, R_APPEND_OP, 2) != NULL);
	return (-1);
}

static int	ft_is_soperator(const char *str, t_operators op)
{
	if (op == PIPE)
		return (str[0] == PIPE_OP[0] && str[1] != PIPE_OP[0]);
	if (op == L_REDIRECT)
		return (str[0] == L_REDIRECT_OP[0] && str[1] != L_REDIRECT_OP[0]);
	if (op == R_REDIRECT)
		return (str[0] == R_REDIRECT_OP[0] && str[1] != R_REDIRECT_OP[0]);
	if (op == L_PARANTHESE)
		return (str[0] == L_PARANTHESE_OP[0]);
	if (op == R_PARANTHESE)
		return (str[0] == R_PARANTHESE_OP[0]);
	if (op == L_CBRACKET)
		return (str[0] == L_CBRACKET_OP[0]);
	if (op == R_CBRACKET)
		return (str[0] == R_CBRACKET_OP[0]);
	if (op == L_BRACKET)
		return (str[0] == L_BRACKET_OP[0]);
	if (op == R_BRACKET)
		return (str[0] == R_BRACKET_OP[0]);
	return (-1);
}

int	ft_is_operator(char *str, t_operators op)
{
	char	**operators;

	if (!str)
		return (-1);
	operators = get_operators();
	if (ft_strlen(str) < ft_strlen(operators[op]))
		return (0);
	if (op == AND || op == OR || op == L_DELIMITER
		|| op == R_APPEND)
		return (ft_is_doperator(str, op));
	return (ft_is_soperator(str, op));
}
