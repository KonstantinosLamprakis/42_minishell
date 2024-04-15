/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:47:11 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:33:07 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	ft_strswapc(char *str, int index1, int index2)
{
	int	tmp;

	tmp = str[index1];
	str[index1] = str[index2];
	str[index2] = tmp;
}

void	ft_strreverse(char *str)
{
	int	half_len;
	int	offset;

	if (!str || !str[0])
		return ;
	half_len = ft_strlen(str) / 2;
	offset = -1;
	while (++offset < half_len)
		ft_strswapc(str, offset, ft_strlen(str) - offset - 1);
}
