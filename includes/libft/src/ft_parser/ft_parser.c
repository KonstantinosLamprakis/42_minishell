/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:24:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/16 12:33:06 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

/*	Flow:
		- when a token is found, create a new btree_node
		-
*/

/**
 * @brief Parses str respecting operators such as '()' or '""'
 * 	and using c as basic word separator
 *
 * @param str string to parse
 * @return char** parsed list of strings
 */
void	ft_parse(const char *str)
{
	t_btree	*syntaxic_tree;
	int		index;
	int		token_count;
	t_token	*token;

	if (!str)
		return (set_error((char *)__func__, INVALID_ARG));
	token_count = 0;
	token = ft_tokenize(str, &token_count);
	if (!token)
		return ;
	index = -1;

	free(token);
}
