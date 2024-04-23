/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:08:59 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 13:39:39 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Applies ft_substr and ft_strtrim_if to get a trimmed substring
 *
 * @param str
 * @param start
 * @param len
 * @param cmp
 * @return char*
 */
char	*ft_substr_if(char *str, int start, int len, int (*cmp)(int))
{
	char	*tmp;
	char	*res;

	if (!str || start < 0 || len < 0 || !cmp)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	tmp = ft_substr(str, start, len);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	res = ft_strtrim_if(tmp, cmp);
	if (!res)
		return (free(tmp), set_error((char *)__func__, ALLOC), NULL);
	return (free(tmp), res);
}
