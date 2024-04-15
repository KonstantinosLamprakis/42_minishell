/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:12:13 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:35:28 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;
	unsigned char	ref;

	if (!c)
		return ((char *)(s + ft_strlen(s)));
	ptr = (unsigned char *)s;
	ref = (unsigned char)c;
	while (*ptr && *ptr != ref)
		ptr++;
	if (*ptr == ref)
		return ((char *)ptr);
	return (NULL);
}
