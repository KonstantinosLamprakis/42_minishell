/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:20:03 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:25:33 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"

static int	ft_convert_to(unsigned int n, char *buffer, int lower)
{
	int	r;
	int	buffer_len;

	buffer_len = 0;
	while (n >= 16)
	{
		r = n % 16;
		buffer[buffer_len++] = (r + (r < 10) * '0' + (r >= 10) * ('A' - 10
					+ (lower * 32)));
		n /= 16;
	}
	buffer[buffer_len++] = (n + (n < 10) * '0' + (n >= 10) * ('A' - 10 + (lower
					* 32)));
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

char	*ft_htoa(unsigned int n, int lower)
{
	char	*res;
	char	buffer[16];
	int		buf_len;

	res = malloc(11 * sizeof(char));
	if (!res)
		return (NULL);
	res[10] = '\0';
	buf_len = ft_convert_to(n, buffer, lower);
	ft_rev_buffer(buffer, buf_len, res);
	return (res);
}
