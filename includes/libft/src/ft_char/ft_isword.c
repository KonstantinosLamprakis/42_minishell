/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isword.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:39:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 11:43:56 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"

/**
 * @brief Returns whether or not str will be entering a new word
 * by checking if the character pointed by str is a separator
 * and the next one is in a word
 *
 * @param str
 * @param is_sep
 * @return int
 */
int	ft_isword(char *str, int (*is_sep)(int))
{
	return ((*is_sep)(str[0]) && !(*is_sep)(str[1]));
}
