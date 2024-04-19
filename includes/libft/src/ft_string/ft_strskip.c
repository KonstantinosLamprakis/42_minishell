/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strskip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:25:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 11:34:38 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Returns the pointer to the first character in str
 * for which cmp return 0
 *
 * @param str
 * @param cmp
 * @param is_eol optionnal boolean where the fct will store whether or not
 * it reached the end of str
 * @return char*
 */
char	*ft_strskip(char *str, int (*cmp)(int), int *is_eol)
{
	int	index;

	index = 0;
	while (str[index] && (*cmp)(str[index]))
		index++;
	if (is_eol)
		*is_eol = (str[index] == '\0');
	return (&str[index]);
}
