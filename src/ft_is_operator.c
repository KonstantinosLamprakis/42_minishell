/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:21:20 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 13:37:21 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_doperator(const char *str, int op)
{
	if (op == AND && ft_strncmp(str, AND_OP, 2) == 0)
	{
		if (ft_strlen(str) >= 2 && str[2] == AND_OP[0])
			return (set_error((char *)__func__, SYNTAX), -1);
		return (1);
	}
	if (op == OR && ft_strncmp(str, OR_OP, 2) == 0)
	{
		if (ft_strlen(str) >= 2 && str[2] == OR_OP[0])
			return (set_error((char *)__func__, SYNTAX), -1);
		return (1);
	}
	if (op == L_DELIMITER && ft_strncmp(str, L_DELIMITER_OP, 2) == 0)
	{
		if (ft_strlen(str) >= 2 && str[2] == L_DELIMITER_OP[0])
			return (set_error((char *)__func__, SYNTAX), -1);
		return (1);
	}
	if (op == R_APPEND && ft_strncmp(str, R_APPEND_OP, 2) == 0)
	{
		if (ft_strlen(str) >= 2 && str[2] == R_APPEND_OP[0])
			return (set_error((char *)__func__, SYNTAX), -1);
		return (1);
	}
	return (-1);
}

static int	ft_is_soperator(const char *str, int op)
{
	if (op == PIPE)
		return (str[0] == PIPE_OP[0] && (ft_strlen(str) <= 1
				|| str[1] != PIPE_OP[0]));
	if (op == L_REDIRECT)
		return (str[0] == L_REDIRECT_OP[0] && (ft_strlen(str) <= 1
				|| str[1] != L_REDIRECT_OP[0]));
	if (op == R_REDIRECT)
		return (str[0] == R_REDIRECT_OP[0] && (ft_strlen(str) <= 1
				|| str[1] != R_REDIRECT_OP[0]));
	return (-1);
}

int	ft_is_operator(char *str, int op)
{
	char	**operators;

	if (!str)
		return (-1);
	operators = get_operators();
	if (ft_strlen(str) < ft_strlen(operators[op]))
		return (0);
	if (op == AND || op == OR || op == L_DELIMITER || op == R_APPEND)
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
