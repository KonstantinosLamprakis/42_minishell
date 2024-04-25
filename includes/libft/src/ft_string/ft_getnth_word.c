/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnth_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:44:37 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 10:14:54 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Extracts the nth word from str, defining a word by is_sep
 * and if not NULL, trimms it using cmp
 *
 * @param str
 * @param n
 * @param is_sep
 * @param cmp
 * @return char*
 */
char	*ft_getnth_word(char *str, int n, int (*is_sep)(int), int (*cmp)(int))
{
	char	*word;
	int		start;
	int		index;

	if (!str || n < 0 || !is_sep)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	index = -1;
	n -= !(*is_sep)(str[0]);
	start = (*is_sep)(str[0]);
	while (str[++index] && n >= 0)
	{
		if (ft_isword(str + index, is_sep))
			if (n-- == 1)
				start = index + (*is_sep)(str[index]);
	}
	if (n > 1)
		return (NULL);
	if (!cmp)
		word = ft_substr(str, start, index - start);
	else
		word = ft_substr_if(str, start, index - start, cmp);
	if (*get_errno() != 0)
		return (NULL);
	return (word);
}
