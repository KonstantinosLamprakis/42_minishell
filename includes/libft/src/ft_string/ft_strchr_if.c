/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:43:16 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 13:44:32 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Returns the pointer the first char in str that returns 1 with cmp
 *
 * @param str
 * @param cmp
 * @return char*
 */
char	*ft_strchr_if(char *str, int (*cmp)(int))
{
	int	index;

	index = -1;
	while (str[++index])
		if ((*cmp)(str[index]))
			break ;
	return (str + index);
}
