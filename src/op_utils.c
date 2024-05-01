/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:01:14 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 17:04:34 by lgreau           ###   ########.fr       */
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
		if (ft_isquote(str[index]))
		{
			index += skip_quotes(str + index, str[index]);
			continue ;
		}
		op = -1;
		while (++op < OPERATOR_COUNT)
			if (ft_is_operator(str + index, op) == 1
				|| ft_is_encapsulator(str[index]) == 1)
				return (index);
	}
	return (-1);
}

int	setup_write_pipe(void)
{
	t_program	*program;

	program = get_program();
	if (dup2(program->pipe_save_write[program->depth], STDOUT) < 0)
		return (set_error((char *)__func__, DUP), 0);
	close(program->pipe_save_read[program->depth]);
	return (1);
}
