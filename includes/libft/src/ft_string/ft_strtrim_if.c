/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:59:42 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 10:04:13 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Trims the input string by every character recognized by cmp
 *
 * @param str
 * @param cmp should return 1 if the char has to be trimmed
 * @return char*
 */
char	*ft_strtrim_if(char *str, int (*cmp)(int))
{
	int	count;
	int	index;

	if (!str || !cmp)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	count = 0;
	index = ft_strlen(str);
	while (str[--index] && (*cmp)(str[index]))
		count++;
	index = -1;
	while (str[++index] && (*cmp)(str[index]))
		count++;
	return (ft_substr(str, index, ft_strlen(str) - count));
}
