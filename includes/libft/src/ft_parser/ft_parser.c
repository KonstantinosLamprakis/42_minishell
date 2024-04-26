/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:24:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 08:52:20 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static int	handle_found_encapsulator(t_token *token, char *str, int start,
		t_encapsulators enc)
{
	token->start = start;
	token->enc = enc;
	token->op = -1;
	if (enc == L_PARANTHESE)
		token->end = token->start + endof_paranthese(str, start);
	// if (enc == L_CBRACKET)
	// 	token->end = token->start + endof_cbrackets(str, start);
	// if (enc == L_BRACKET)
	// 	token->end = token->start + endof_brackets(str, start);
	return (1);
}

static int	handle_found_operator(t_token *token, int index, t_operators op)
{
	token->op = op;
	token->enc = -1;
	token->start = index;
	return (1);
}

/**
 * @brief Finds the next token, searchin for the biggest precedence and skipping
 * encapsulations such as () {} or []
 *
 * @param str
 * @param token to save the values in
 * @return int whether a token has been found or not
 */
static int	find_next_token(char *str, t_token *token)
{
	int	index;
	int	token_c;

	index = -1;
	token->start = -1;
	while (str[++index])
	{
		token_c = ft_which_op(str + index);
		if (token_c >= 0 && handle_found_operator(token, index, token_c))
			break ;
		token_c = ft_which_enc(str + index);
		if (token_c >= 0 && handle_found_encapsulator(token, str, index,
				token_c))
			break ;
	}
	if (token->start < 0)
		return (0);
	return (1);
}

static void	save_next(char *str, t_token *token)
{
	int	index;

	index = token->start;
	token->next_operator = -1;
	while (str[++index])
	{
		if (ft_which_op(str + index) >= 0 || ft_which_enc(str
					+ index) >= 0)
		{
			token->next_operator = index;
			break ;
		}
	}
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
	char				*sub;

	/*	For printing purposes	*/
	int		*lengths;
	char	**operators;
	char	**encapsulators;
	operators = get_operators();
	encapsulators = get_encapsulators();
	lengths = get_lengths();

	token.start = -1;
	token.op = -1;
	token.str = str;
	handlers = get_handlers();
	printf("\n%s input: \"%s\"\n", (char *)__func__, str);
	if (ft_strlen_if(str, ft_iswspace) > 0 && find_next_token(str, &token) >= 0)
	{
		if (token.start < 0)// && printf("No operators in \"%s\".\n", str))
		{
			printf(DEBUG_START_HANDLER);
			offset = handlers[OPERATOR_COUNT]((void *)&token);
			printf(DEBUG_END_OF_HANDLER);
			printf("Parser must skip %d char.\n", offset);
			printf("Starting next iteration from %s\n", str + offset);
			if (offset < 0)
			{
				if (*get_errno() != 0)// && printf("Something went wrong in thep previous hanlder.\n"))
					return ;
				//printf("The parsing finished without problem.\n");
				return ;
			}
		}
		else
		{
			printf("Next token is \"%s\"\n", str + token.start);
			save_next(str, &token);
			if ((int)token.op >= 0)
			{
				printf("Operator found %d : %s.\n", token.op, operators[token.op]);
				printf(DEBUG_START_HANDLER);
				offset = handlers[token.op]((void *)&token);
				printf(DEBUG_END_OF_HANDLER);
				printf("Parser must skip %d char.\n", offset);
				printf("Starting next iteration from %s\n", str + offset);
				if (offset < 0)
				{
					if (*get_errno() != 0)// && printf("Something went wrong in thep previous hanlder.\n"))
						return ;
					//printf("The parsing finished without problem.\n");
					return ;
				}
				ft_parse(str + offset);
			}
			if ((int)token.enc >= 0)
			{
				printf("Encapsulator found %d : %s.\n", token.enc, encapsulators[token.enc]);
				printf("Encapsulator ends @ %d: %s\n", token.end, token.str + token.end);
				sub = ft_substr(token.str, token.start + 1, token.end - token.start - 1);
				if (!sub)
					return (set_error((char *)__func__, ALLOC));
				printf("sub = %s\n", sub);
				ft_parse(sub);
				free(sub);
				ft_parse(str + token.end + 1);
			}
		}
	}
}
