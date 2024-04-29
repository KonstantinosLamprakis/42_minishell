/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parantheses_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:29:55 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 12:56:42 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Parses the sub shell command line str
 *
 * @param str
 */
static void	ft_parse_sub(char *str)
{
	t_token				token;
	t_operator_handler	*handlers;
	int					offset;

	token.start = -1;
	token.enc = -1;
	token.op = -1;
	token.str = str;
	handlers = get_handlers();
	if (ft_strlen_if(str, ft_iswspace) > 0 && find_next_token(str, &token) >= 0)
	{
		if ((int)token.op < 0)
		{
			if ((int)token.enc >= 0)
			{
				offset = handlers[OPERATOR_COUNT + 1]((void *)&token);
				if (offset < 0)
					return ;
				ft_parse_sub(str + offset);
			}
			else
			{
				get_program()->depth--;
				get_program()->is_piped = 1;
				handlers[OPERATOR_COUNT]((void *)&token);
				get_program()->is_piped = 0;
			}
		}
		else
		{
			offset = handlers[token.op]((void *)&token);
			if (offset < 0)
				return ;
			ft_parse_sub(str + offset);
		}
	}
}

int	parantheses_handler(void *arg)
{
	t_token		*token;
	t_program	*program;
	char		*sub;

	token = (t_token *)arg;
	program = get_program();
	program->depth++;
	sub = ft_substr(token->str, token->start + 1, token->end - token->start - 1);
	if (!sub)
		return (set_error((char *)__func__, ALLOC), -1);
	ft_parse_sub(sub);
	return (-1);
}
