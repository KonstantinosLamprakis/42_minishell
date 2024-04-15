/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:03:41 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:33:28 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

int	ft_putnbr_base_fd(char *n, char *base, int fd)
{
	int				index;
	long long int	dec;

	if (!n || !base || !base[0] || !base[1])
		return (-1);
	index = -1;
	dec = 0;
	while (n[++index])
		dec = dec * ft_strlen(base) + ft_strcindex(base, n[index]);
	if (dec > INT_MAX || (dec < 0 && dec < INT_MIN))
		return (-1);
	return (ft_putnbr_fd((int)dec, fd));
}

int	ft_putnbr_base(char *n, char *base)
{
	return (ft_putnbr_base_fd(n, base, 1));
}
