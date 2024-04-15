/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:06:12 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"

static int	ft_convert_to(long long int n, char *buffer)
{
	int	buffer_len;

	buffer_len = 0;
	while (n >= 10)
	{
		buffer[buffer_len++] = (n % 10) + '0';
		n /= 10;
	}
	buffer[buffer_len++] = n + '0';
	buffer[buffer_len] = '\0';
	return (buffer_len);
}

static void	ft_rev_buffer(char *buffer, int buffer_len, char *dup)
{
	int	offset;

	offset = 0;
	while (--buffer_len >= 0)
		dup[offset++] = buffer[buffer_len];
	dup[offset] = '\0';
}

char	*ft_itoa(int n)
{
	char			*res;
	char			buffer[16];
	int				buf_len;
	long long int	dec;

	dec = ((long long)n) * (1 - 2 * (n < 0));
	buf_len = ft_convert_to(dec, buffer);
	res = malloc((buf_len + 1 + (n < 0)) * sizeof(char));
	if (!res)
		return (NULL);
	res[buf_len + (n < 0)] = '\0';
	if (n < 0)
		res[0] = '-';
	ft_rev_buffer(buffer, buf_len, res + (n < 0));
	return (res);
}
