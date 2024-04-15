/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:51:29 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:32:30 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ref;

	if (n)
	{
		ptr = (unsigned char *)s;
		ref = (unsigned char)c;
		while (*ptr != ref && --n)
			ptr++;
		if (*ptr == ref)
			return ((char *)ptr);
	}
	return (NULL);
}
