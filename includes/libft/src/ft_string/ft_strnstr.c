/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:24:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 08:40:20 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ptr;
	size_t	offset;

	if (!*needle)
		return ((char *)haystack);
	ptr = (char *)haystack;
	offset = 0;
	while (*ptr && len)
	{
		if (*ptr == *needle)
		{
			offset = 0;
			while (ptr[offset] && ptr[offset] == needle[offset] && (len
					- offset))
				offset++;
			if (!needle[offset])
				return (ptr);
		}
		ptr++;
	}
	return (NULL);
}
