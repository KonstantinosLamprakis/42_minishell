/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:24:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 18:25:04 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

/*	Flow:
		- when a token is found, create a new btree_node
		-
*/

static int	skip_subtree(char *str, int start, t_operators op)
{
	if (op == L_PARANTHESE)
		return (endof_paranthese(str, start));
	if (op == L_CBRACKET)
		return (endof_paranthese(str, start));
	if (op == L_BRACKET)
		return (endof_paranthese(str, start));
	return (-1);
}

static void	handle_found_token(char *str, t_token *token, int *index, int *max)
{
	int	*precedences;

	precedences = get_precedence();
	if (precedences[token->current_op] > *max)
	{
		token->start = *index;
		token->op = token->current_op;
		*max = precedences[token->op];
	}
	if (ft_is_encapsulator(token->current_op))
		*index += skip_subtree(str, *index, token->current_op);
}

static int find_next_token(char *str, t_token *token)
{
	int	*precedences;
	int	index;
	int	op;
	int	max;

	precedences = get_precedence();
	index = -1;
	max = -1;
	token->start = -1;
	token->op = 0;
	while (str[++index])
	{
		op = ft_which_op(str + index);
		if (op >= 0)
		{
			token->current_op = op;
			handle_found_token(str, token, &index, &max);
			if (*get_errno() != 0)
				return (-1);
		}
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
 * @return char** parsed list of strings
 */
void	ft_parse(char *str)
{
	// t_btree	*syntaxic_tree;
	char	**operators;
	char	*left;
	char	*right;
	t_token	token;

	operators = get_operators();
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
			if (ft_is_encapsulator(token.op) && printf("todo: handle %s\n", operators[token.op]))
				return ;
			printf("token start = %d, %c\n", token.start, str[token.start]);
			left = ft_substr(str, 0, token.start);
			ft_parse(left);
			free(left);
			right = ft_substr(str, token.start + ft_strlen(operators[token.op]) + 1, ft_strlen(str) - token.start + ft_strlen(operators[token.op]) + 1);
			// printf("|%s|\n", right);
			ft_parse(right);
			free(right);
		}
	}
}
