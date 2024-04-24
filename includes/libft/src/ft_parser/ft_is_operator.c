/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:21:20 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 09:39:16 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static int	ft_is_doperator(const char *str, t_operators op)
{
	if (op == AND)
		return (ft_strncmp(str, AND_OP, 2) == 0);
	if (op == OR)
		return (ft_strncmp(str, OR_OP, 2) == 0);
	if (op == L_DELIMITER)
		return (ft_strncmp(str, L_DELIMITER_OP, 2) == 0);
	if (op == R_APPEND)
		return (ft_strncmp(str, R_APPEND_OP, 2) == 0);
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

int	ft_which_op(char *str)
{
	int	index;

	index = -1;
	while (++index < OPERATOR_COUNT)
		if (ft_is_operator(str, index) > 0)
			return (index);
	return (-1);
}
