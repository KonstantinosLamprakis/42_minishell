/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:56:13 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 08:32:36 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	or_handler(void *arg)
{
	t_program	*program;
	t_token		*token;
	char		*left_arg;

	token = (t_token *)arg;
	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), -1);
	}
	or_operation(left_arg);
	if (left_arg)
		free(left_arg);
	program = get_program();
	if (program->status == 0)
		return (-1);
	if (ft_strnstr(token->str, "||", 2) == NULL)
		return (-1);
	return ((ft_strnstr(token->str, "||", 2) - token->str) + 2);
}

void	or_operation(char *left_arg)
{
	ft_parse(left_arg);
}
