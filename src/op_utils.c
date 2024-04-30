/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:01:14 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 15:43:06 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_op(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
		if (ft_which_op(str + index) >= 0 || ft_which_enc(str + index) >= 0)
			return (1);
	return (0);
}

/**
 * @brief Returns the index of the first operator found, or \0 if none found.
 *
 * @param str
 * @return int
 */
int	ft_strop(char *str)
{
	int	index;
	int	op;

	index = -1;
	while (str[++index])
	{
		op = -1;
		while (++op < OPERATOR_COUNT)
			if (ft_is_operator(str + index, op) == 1
				|| ft_is_encapsulator(str[index]) == 1)
				return (index);
	}
	return (index);
}
