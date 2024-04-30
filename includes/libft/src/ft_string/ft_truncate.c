/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_truncate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:14:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 13:18:52 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Truncates str ltruncate("abcde", 2) will return "ab"
 *
 * @param str
 * @param count
 * @return char* NOT ALLOCATED
 */
char	*ft_ltruncate(char *str, size_t len)
{
	if (!str || ft_strlen(str) < len)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	str[len] = 0;
	return (str);
}

/**
 * @brief Truncates str from the end, rtruncate("abcde", 2) will return "abc"
 *
 * @param str
 * @param count
 * @return char* NOT ALLOCATED
 */
char	*ft_rtruncate(char *str, size_t count)
{
	if (!str || count > ft_strlen(str))
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	str[ft_strlen(str) - count - 1] = 0;
	return (str);
}
