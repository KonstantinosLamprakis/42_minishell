/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parantheses_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:29:55 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 12:46:55 by lgreau           ###   ########.fr       */
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
	// char				*sub;

	/*	For printing purposes	*/
	int		*lengths;
	char	**operators;
	char	**encapsulators;
	operators = get_operators();
	encapsulators = get_encapsulators();
	lengths = get_lengths();

	token.start = -1;
	token.enc = -1;
	token.op = -1;
	token.str = str;
	handlers = get_handlers();
	// printf("\n%s input: \"%s\"\n", (char *)__func__, str);
	if (ft_strlen_if(str, ft_iswspace) > 0 && find_next_token(str, &token) >= 0)
	{
		if ((int)token.op < 0)
		{
			if ((int)token.enc >= 0)
			{
				offset = handlers[OPERATOR_COUNT + 1]((void *)&token);
				//printf("Encapsulator found %d : %s.\n", token.enc, encapsulators[token.enc]);
				//printf("Encapsulator ends @ %d: %s\n", token.end, token.str + token.end);
				// sub = ft_substr(token.str, token.start + 1, token.end - token.start - 1);
				// if (!sub)
				// 	return (set_error((char *)__func__, ALLOC));
				// //printf("sub = %s\n", sub);
				// ft_parse(sub);
				// free(sub);
				//printf("DEBUG: (%d) %s\n", token.end, str + token.end + 1);
				if (offset < 0)
					return ;
				ft_parse_sub(str + offset);
			}
			else
			{
				// printf(DEBUG_START_HANDLER);
				// printf("Last command detected (no more operators or parantheses): %s\n", str);
				// if (setup_last_cmd() != NO_ERROR)
				// 	return ;
				get_program()->depth--;
				get_program()->is_piped = 1;
				handlers[OPERATOR_COUNT]((void *)&token);
				get_program()->is_piped = 0;
				//printf(DEBUG_END_OF_HANDLER);
			}
		}
		else
		{
			////printf("Next token is \"%s\"\n", str + token.start);
			////printf("Operator found %d : %s.\n", token.op, operators[token.op]);
			////printf(DEBUG_START_HANDLER);
			offset = handlers[token.op]((void *)&token);
			////printf(DEBUG_END_OF_HANDLER);
			////printf("Parser must skip %d char.\n", offset);
			////printf("Starting next iteration from %s\n", str + offset);
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
