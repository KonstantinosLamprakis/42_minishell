/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:28:35 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:35:59 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static size_t	min(size_t s_len, unsigned int start, size_t len)
{
	if (start > s_len)
		return (0);
	if (len < (s_len - start))
		return (len);
	return (s_len - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	offset;
	size_t	s_len;
	size_t	sub_len;

	s_len = ft_strlen(s);
	sub_len = min(s_len, start, len);
	sub = malloc((sub_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	offset = 0;
	if (start < s_len)
	{
		while ((offset + start) < s_len && s[offset + start] && offset < len)
		{
			sub[offset] = s[offset + start];
			offset++;
		}
	}
	sub[offset] = '\0';
	return (sub);
}
