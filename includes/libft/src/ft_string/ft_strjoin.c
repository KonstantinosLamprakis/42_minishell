/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:13:05 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:38:36 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, s1_len);
	ft_memcpy((res + s1_len), s2, s2_len);
	res[s1_len + s2_len] = '\0';
	return (res);
}

char	*ft_strjoinline(char const *s1, char const *s2, size_t len)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	min;
	char	*eol;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	eol = ft_strchr(s2, '\n');
	min = (s2_len * (s2_len <= len) + len * (s2_len > len));
	if (eol != NULL)
		min = (eol + 1 - s2);
	res = malloc((s1_len + min + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_memmove(res, s1, s1_len);
	ft_memmove((res + s1_len), s2, min);
	res[s1_len + min] = '\0';
	return (res);
}
