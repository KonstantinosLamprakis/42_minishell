/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:26:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 13:26:51 by lgreau           ###   ########.fr       */
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

char	*ft_ultoa(unsigned long int n)
{
	char					*res;
	char					buffer[16];
	int						buf_len;
	unsigned long long int	dec;

	dec = ((long long)n);
	buf_len = ft_convert_to(dec, buffer);
	res = malloc((buf_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[buf_len] = '\0';
	ft_rev_buffer(buffer, buf_len, res);
	return (res);
}
