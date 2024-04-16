/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encapsulators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:41:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 15:06:05 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

int	endof_paranthese(char *str, t_token *token)
{
	int	index;
	int	count;
	int	op;

	index = 0;
	count = 1;
	while (str[++index + token->start])
	{
		op = ft_which_op(str + token->start + index);
		if (op >= 0 && (op == L_PARANTHESE || op == R_PARANTHESE))
			count += ft_is_encapsulator_start(op) - ft_is_encapsulator_end(op);
		if (count == 0)
		{
			token->end = index;
			break ;
		}
	}
	if (count != 0)
		return (set_error((char *)__func__, SYNTAX), -1);
	return (index + 1);
}

int	endof_cbrackets(char *str, t_token *token)
{
	int	index;
	int	count;
	int	op;

	index = 0;
	count = 1;
	while (str[++index + token->start])
	{
		op = ft_which_op(str + token->start + index);
		if (op >= 0 && (op == L_CBRACKET || op == R_CBRACKET))
			count += ft_is_encapsulator_start(op) - ft_is_encapsulator_end(op);
		if (count == 0)
		{
			token->end = index;
			break ;
		}
	}
	if (count != 0)
		return (set_error((char *)__func__, SYNTAX), -1);
	return (index + 1);
}

int	endof_brackets(char *str, t_token *token)
{
	int	index;
	int	count;
	int	op;

	index = 0;
	count = 1;
	while (str[++index + token->start])
	{
		op = ft_which_op(str + token->start + index);
		if (op >= 0 && (op == L_BRACKET || op == R_BRACKET))
			count += ft_is_encapsulator_start(op) - ft_is_encapsulator_end(op);
		if (count == 0)
		{
			token->end = index;
			break ;
		}
	}
	if (count != 0)
		return (set_error((char *)__func__, SYNTAX), -1);
	return (index + 1);
}
