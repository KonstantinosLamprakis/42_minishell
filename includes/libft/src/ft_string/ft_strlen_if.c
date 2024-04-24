/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:47:32 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 09:49:49 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Returns the lenght of what a trimmed str by cmp would be
 *
 * @param str
 * @param cmp
 * @return size_t
 */
size_t	ft_strlen_if(char *str, int (*cmp)(int))
{
	size_t	len;
	char	*tmp;

	if (!str || !cmp)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	tmp = ft_strtrim_if(str, cmp);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), 0);
	len = ft_strlen(tmp);
	return (free(tmp), len);
}
