/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:24:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/17 09:29:51 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

/*	Flow:
		- when a token is found, create a new btree_node
		-
*/

static int	handle_found_encapsulator(t_token *token, char *str, int start,
		t_encapsulators enc)
{
	token->start = start;
	token->enc = enc;
	token->op = -1;
	if (enc == L_PARANTHESE)
		token->end = token->start + endof_paranthese(str, start);
	if (enc == L_CBRACKET)
		token->end = token->start + endof_cbrackets(str, start);
	if (enc == L_BRACKET)
		token->end = token->start + endof_brackets(str, start);
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

/**
 * @brief Parses str respecting operators such as '()' or '""'
 * 	and using c as basic word separator
 *
 * @param str string to parse
 */
void	ft_parse(char *str)
{
	int		*lengths;
	// char	*left;
	// char	*right;
	t_token	token;

	char	**operators = get_operators();
	char	**encapsulators = get_encapsulators();

	// t_btree	*syntaxic_tree;
	lengths = get_lengths();
	token.start = -1;
	token.op = -1;
	printf("\n%s input: \"%s\"\n", (char *)__func__, str);
	if (find_next_token(str, &token) >= 0)
	{
		if (token.start < 0)
			printf("No operators in \"%s\".\n", str);
		else
		{
			printf("Next token is \"%s\"\n", str + token.start);
			if ((int)token.op >= 0)
				printf("Operator found %d : %s.\n", token.op, operators[token.op]);
			if ((int)token.enc >= 0)
				printf("Encapsulator found %d : %s.\n", token.enc, encapsulators[token.enc]);
		}
	}
}
