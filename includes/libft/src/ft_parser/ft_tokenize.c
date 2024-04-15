/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:57:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/15 11:22:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

/**
 * @brief Tries every operators to see if the current char is part of an
 * operator token, if so, saves it.
 *
 * @param str to parse
 * @param token list of tokens
 * @param token_c number of tokens already in the list
 * @return int number of char to skip in str.
 */
static int	ft_parse_token(char *str, t_token *token, int *token_count)
{
	char	**operators;
	int		index;

	operators = get_operators();
	index = -1;
	while (++index < OPERATOR_COUNT)
	{
		if (ft_is_operator(str, index))
		{
			token[*token_count].op = index;
			token[*token_count].value = str;
			(*token_count)++;
			return (ft_strlen(operators[index]));
		}
	}
	return (1);
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

	token = malloc(ft_strlen(str) * sizeof(t_token));
	if (!token)
		return (set_error((char *)__func__, ALLOC), NULL);
	*token_count = 0;
	index = 0;
	while (str[index])
		index += ft_parse_token(str + index, token, token_count);
	return (token);
}
