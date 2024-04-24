/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:59:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 09:41:33 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief "<<" operator handler, expects a string as right argument
 *
 * @param arg
 * @return int
 */
int	l_delimiter_handler(void *arg)
{
	t_token	*token;
	int		offset;
	char	*left_arg;
	char	*right_arg;
	char	*tmp;

	token = (t_token *)arg;

	printf("\n%s: received token:\n", (char *)__func__);
	printf("  |- string: %s\n", token->str);
	printf("  |- start : %s\n", token->str + token->start);

	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start - 1, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), -1);
	}
	printf("  |- left_arg  = %s\n", left_arg);

	tmp = ft_getnth_word(token->str + token->start + 2, 1, ft_iswspace, NULL);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), -1);
	right_arg = ft_strtrim_if(tmp, ft_iswspace);
	free(tmp);
	if (!right_arg)
		return (-1);
	printf("  |- right_arg = %s\n\n", right_arg);

	if (ft_strnstr(token->str, right_arg, ft_strlen(right_arg)) == NULL)
		return (-1);
	offset = (ft_strnstr(token->str, right_arg, ft_strlen(right_arg)) - token->str) + ft_strlen(right_arg);
	return (offset);
}
