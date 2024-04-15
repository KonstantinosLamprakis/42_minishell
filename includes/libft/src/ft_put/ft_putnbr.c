/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:32:55 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

static int	ft_put_buffer_fd(char *buffer, int fd, int is_neg)
{
	int		count;
	size_t	buffer_len;

	buffer_len = ft_strlen(buffer);
	count = is_neg;
	if (is_neg && write(fd, "-", 1) >= 0)
		;
	while (--buffer_len >= 0)
		count += write(fd, &buffer[buffer_len], 1);
	return (count);
}

int	ft_putnbr_fd(int n, int fd)
{
	char	buffer[INT_MAX_LOG];
	int		nbr;
	int		index;

	if (n == INT_MIN && write(fd, "-2147483648", 11) >= 0)
		return (11);
	nbr = (1 - 2 * (n < 0)) * n;
	index = 0;
	while (nbr > 0)
	{
		buffer[index++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	buffer[index] = 0;
	return (ft_put_buffer_fd(buffer, fd, (n < 0)));
}

int	ft_putnbr(int n)
{
	return (ft_putnbr_fd(n, 1));
}
