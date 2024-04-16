/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:57:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 15:06:48 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static int	find_endof_encapsulator(char *str, t_token *token)
{
	char	**operators;

	operators = get_operators();
	if (token->op == L_PARANTHESE)
		return (endof_paranthese(str, token));
	if (token->op == L_CBRACKET)
		return (endof_cbrackets(str, token));
	if (token->op == L_BRACKET)
		return (endof_brackets(str, token));
	return (ft_strlen(operators[token->op]));
}

/**
 * @brief Tries every operators to see if the current char is part of an
 * operator token, if so, saves it.
 *
 * @param str to parse
 * @param token list of tokens
 * @param token_c number of tokens already in the list
 * @return int number of char to skip in str.
 */
static int	ft_parse_token(char *str, int offset, t_token *token,
		int *token_count)
{
	char	**operators;
	int		*precedences;
	int		index;

	operators = get_operators();
	precedences = get_precedence();
	index = -1;
	while (++index < OPERATOR_COUNT)
	{
		if (ft_is_operator(str + offset, index))
		{
			if (ft_is_encapsulator_end(index))
				return (set_error((char *)__func__, SYNTAX), -1);
			token[*token_count].op = index;
			token[*token_count].op_precedence = precedences[index];
			token[*token_count].start = offset;
			if (*token_count > 0)
				token[(*token_count) - 1].next = offset;
			token[*(token_count)].end = -1;
			return (find_endof_encapsulator(str, &token[(*token_count)++]));
		}
	}
	return (1);
}

/**
 * @brief Swaps all the values in token[index1] & token[index2]
 *
 * @param token
 * @param index1
 * @param index2
 */
static void	swap_tokens(t_token *token, int index1, int index2)
{
	t_token	tmp;

	tmp.op = token[index1].op;
	tmp.op_precedence = token[index1].op_precedence;
	tmp.start = token[index1].start;
	tmp.end = token[index1].end;
	tmp.next = token[index1].next;
	token[index1].op = token[index2].op;
	token[index1].op_precedence = token[index2].op_precedence;
	token[index1].start = token[index2].start;
	token[index1].end = token[index2].end;
	token[index1].next = token[index2].next;
	token[index2].op = tmp.op;
	token[index2].op_precedence = tmp.op_precedence;
	token[index2].start = tmp.start;
	token[index2].end = tmp.end;
	token[index2].next = tmp.next;
}

/**
 * @brief Sorts the tokens in token by descending precedence
 *
 * @param token array to sort
 * @param token_count
 */
static void	ft_sort_tokens(t_token *token, int token_count)
{
	int	index;

	while (--token_count > 0)
	{
		index = 0;
		while (++index <= token_count)
		{
			if (token[index - 1].op_precedence < token[index].op_precedence)
				swap_tokens(token, index - 1, index);
		}
	}
}

/**
 * @brief Breaks the input string into tokens, which have both the token type
 * and the pointer towards it's start in the string.
 *
 * @param str to tokenize
 * @param token_count number of tokens found
 * @return t_token* array of tokens
 */
t_token	*ft_tokenize(char *str, int *token_count)
{
	t_token	*token;
	int		index;
	int		offset;

	token = malloc(ft_strlen(str) * sizeof(t_token));
	if (!token)
		return (set_error((char *)__func__, ALLOC), NULL);
	*token_count = 0;
	index = 0;
	while (str[index])
	{
		offset = ft_parse_token(str, index, token, token_count);
		if (offset < 0)
			return (NULL);
		index += offset;
	}
	token[(*token_count) - 1].next = ft_strlen(str);
	ft_sort_tokens(token, *token_count);
	return (token);
}
