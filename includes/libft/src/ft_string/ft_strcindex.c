/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:22:22 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:23:21 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_strcindex(const char *str, int c)
{
	int	index;

	if (!str)
		return (-1);
	index = -1;
	while (str[++index])
		if (str[index] == c)
			return (index);
	return (-1);
}
