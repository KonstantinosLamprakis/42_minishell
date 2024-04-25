/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:39:34 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 11:58:47 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	and_handler(void *arg)
{
	t_program	*program;
	t_token		*token;
	char		*left_arg;

	token = (t_token *)arg;

	printf("\n%s: received token:\n", (char *)__func__);
	printf("  |- string: %s\n", token->str);
	printf("  |- start : %s\n", token->str + token->start);

	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start - 1, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), -1);
	}
	printf("  |- left_arg  = %s\n", left_arg);

	and_operation(left_arg);
	program = get_program();
	if (program->status != 0)
		return (-1);
	if (ft_strnstr(token->str, "&&", 2) == NULL)
		return (-1);
	return ((ft_strnstr(token->str, "&&", 2) - token->str) + 2);
}

void	and_operation(char *left_arg)
{
	ft_parse(left_arg);
}
