/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:44:53 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:11:47 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	sign;
	int	value;

	index = 0;
	while (str[index] && ft_iswspace(str[index]))
		index++;
	sign = 1;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign *= -1;
		index++;
	}
	value = 0;
	while (str[index] && ft_isdigit(str[index]))
		value = value * 10 + ((int)str[index++] - '0');
	return (sign * value);
}
