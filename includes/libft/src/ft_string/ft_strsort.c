/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:33:59 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 13:37:20 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	ft_strsort(char *str)
{
	int	size;
	int	index;

	if (!str)
		return ;
	size = ft_strlen(str);
	while (--size > 0)
	{
		index = 0;
		while (++index < size)
			if (str[index - 1] > str[index])
				ft_strswapc(str, index - 1, index);
	}
}
