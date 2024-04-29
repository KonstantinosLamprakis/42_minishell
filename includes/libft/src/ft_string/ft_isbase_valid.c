/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbase_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:33:21 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 10:52:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_isbase_valid(char *base, char *forbidden_char)
{
	int	index;

	if (!base || ft_strlen(base) < 2)
		return (0);
	if (forbidden_char && ft_strcount_arg(base
			, (int (*)(int, void *))ft_isinbase, (void *)forbidden_char) > 0)
		return (0);
	index = 0;
	ft_strsort(base);
	while (base[++index])
		if (base[index - 1] == base[index])
			return (0);
	return (1);
}
