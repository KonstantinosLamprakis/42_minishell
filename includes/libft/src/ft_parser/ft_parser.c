/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:24:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 10:17:33 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

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
	// char				*sub;

	/*	For printing purposes	*/
	get_operators();
	get_encapsulators();
	get_lengths();

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
				ft_parse(str + offset);
			}
			else
			{
				//printf(DEBUG_START_HANDLER);
				handlers[OPERATOR_COUNT]((void *)&token);
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
			ft_parse(str + offset);
		}
	}
}
