/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:26:10 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:35:55 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*ptr;
	unsigned char	*occ;
	unsigned char	ref;

	ptr = (unsigned char *)s;
	occ = NULL;
	ref = (unsigned char)c;
	if (ref == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (*ptr)
	{
		if (*ptr == ref)
			occ = ptr;
		ptr++;
	}
	return ((char *)occ);
}
