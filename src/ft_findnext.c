/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findnext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:42:34 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 16:52:29 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Finds the next token
 *
 * @param str
 * @param token to save the values in
 * @return int whether a token has been found or not
 */
int	find_next_token(char *str, t_token *token)
{
	int	index;
	int	token_c;

	index = -1;
	token->start = -1;
	while (str[++index])
	{
		if (ft_isquote(str[index]))
		{
			index += skip_quotes(str + index, str[index]);
			continue ;
		}
		token_c = ft_which_op(str + index);
		if (token_c >= 0 && handle_found_operator(token, index, token_c))
			break ;
		token_c = ft_which_enc(str + index);
		if (token_c >= 0 && token->start < 0 && handle_found_encapsulator(token,
				str, index, token_c))
			index += endof_paranthese(str, index) + 1;
		if (*get_errno() != NO_ERROR)
			return (-1);
	}
	if (*get_errno() != NO_ERROR || token->start < 0)
		return (0);
	return (1);
}

void	save_next_token(char *str, t_token *token)
{
	int	index;
	int	token_c;

	index = token->start - 1;
	if (token->op >= 0)
		index += get_lengths()[token->op];
	else
		index++;
	while (str[++index])
	{
		token_c = ft_which_op(str + index);
		if (*get_errno() != NO_ERROR)
			return ;
		if (token_c == PIPE || token_c == OR)
		{
			token->next = index + get_lengths()[token_c];
			return ;
		}
	}
	token->next = -1;
}
