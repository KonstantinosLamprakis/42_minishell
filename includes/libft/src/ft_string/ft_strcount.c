/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 07:41:20 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 13:47:01 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_strcount(const char *str, int (*cmp)(int))
{
	int	count;
	int	index;

	if (!str)
		return (-1);
	index = -1;
	count = 0;
	while (str[++index])
		count += (*cmp)(str[index]);
	return (count);
}

int	ft_strcount_arg(const char *str, int (*cmp)(int, void*), void *arg)
{
	int	count;
	int	index;

	if (!str)
		return (-1);
	index = -1;
	count = 0;
	while (str[++index])
		count += (*cmp)(str[index], arg);
	return (count);
}
