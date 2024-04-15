/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 01:49:16 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:35:32 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strdup(const char *s1)
{
	size_t			src_len;
	char			*dup;
	unsigned int	offset;

	src_len = ft_strlen(s1);
	dup = malloc((src_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	offset = 0;
	while (s1[offset])
	{
		dup[offset] = s1[offset];
		offset++;
	}
	dup[offset] = '\0';
	return (dup);
}
