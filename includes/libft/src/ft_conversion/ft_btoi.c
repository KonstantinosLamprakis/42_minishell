/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:27:56 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:12:00 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"

int	ft_btoi(char *n, char *base)
{
	int				index;
	long long int	dec;

	index = 0;
	dec = 0;
	while (n[index] && ft_strcindex(base, n[index]) >= 0)
		dec = dec * ft_strlen(base) + ft_strcindex(base, n[index++]);
	if (dec > INT_MAX || dec < INT_MIN)
		return (-1);
	return ((int)dec);
}
