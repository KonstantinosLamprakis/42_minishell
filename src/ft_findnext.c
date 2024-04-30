/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findnext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:42:34 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 15:43:17 by lgreau           ###   ########.fr       */
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
	if (*get_errno() != NO_ERROR)
		return (-1);
	if (token->start < 0)
		return (0);
	return (1);
}

void	save_next_token(char *str, t_token *token)
{
	int	index;
	int	token_c;

	index = -1;
	while (str[++index])
	{
		token_c = ft_which_op(str + index);
		if (*get_errno() != NO_ERROR)
			return ;
		if (token_c >= 0)
			break ;
	}
	token->next = index;
}
