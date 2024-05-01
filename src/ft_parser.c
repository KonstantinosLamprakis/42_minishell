/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:24:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 17:21:53 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_token(t_token *token, char *str)
{
	token->start = -1;
	token->enc = -1;
	token->op = -1;
	token->str = str;
}

/**
 * @brief Parses str respecting operators such as '()' or '""'
 * 	and using c as basic word separator
 *
 * @param str string to parse
 */
void	ft_parse(char *str)
{
	t_token				token;
	t_operator_handler	*handlers;
	int					offset;

	init_token(&token, str);
	offset = -1;
	handlers = get_handlers();
	if (ft_strlen_if(str, ft_iswspace) > 0 && find_next_token(str, &token) >= 0)
	{
		if ((int)token.op < 0 && (int)token.enc >= 0)
			offset = handlers[OPERATOR_COUNT + 1]((void *)&token);
		else if ((int)token.op < 0 && (int)token.enc < 0)
			offset = handlers[OPERATOR_COUNT]((void *)&token);
		else
			offset = handlers[token.op]((void *)&token);
	}
	if (offset < 0)
		return ;
	ft_parse(str + offset);
}
