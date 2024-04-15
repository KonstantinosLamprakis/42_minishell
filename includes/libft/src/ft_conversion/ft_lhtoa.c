/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lhtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:33:13 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:28:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"

static int	ft_convert_to(size_t n, char *buffer)
{
	int	r;
	int	buffer_len;

	buffer_len = 0;
	while (n >= 16)
	{
		r = n % 16;
		buffer[buffer_len++] = (r + (r < 10) * '0' + (r >= 10) * ('a' - 10));
		n /= 16;
	}
	buffer[buffer_len++] = (n + (n < 10) * '0' + (n >= 10) * ('a' - 10));
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

char	*ft_lhtoa(size_t n)
{
	char	*res;
	char	buffer[16];
	int		buf_len;

	res = malloc(17 * sizeof(char));
	if (!res)
		return (NULL);
	res[16] = '\0';
	buf_len = ft_convert_to(n, buffer);
	ft_rev_buffer(buffer, buf_len, res);
	return (res);
}
