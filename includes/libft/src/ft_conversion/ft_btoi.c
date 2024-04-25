/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:27:56 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/18 09:45:26 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"

int	ft_btoi(char *n, char *base)
{
	int				index;
	long long int	dec;

	if (!ft_isbase_valid(base, NULL))
		return (set_error((char *)__func__, INVALID_ARG), -1);
	index = 0;
	dec = 0;
	while (n[index] && ft_strcindex(base, n[index]) >= 0)
		dec = dec * ft_strlen(base) + ft_strcindex(base, n[index++]);
	if (dec > INT_MAX || dec < INT_MIN)
		return (set_error((char *)__func__, INVALID_ARG), -1);
	return ((int)dec);
}
