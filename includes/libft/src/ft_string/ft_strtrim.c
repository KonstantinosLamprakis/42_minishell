/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:00:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:46:11 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	set_len;
	size_t	count;
	int		offset;
	int		start;

	if (!s1 || !set)
		return (NULL);
	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	offset = 0;
	count = 0;
	while (s1[offset] && ft_strchr(set, s1[offset]) && count++ >= 0)
		offset++;
	start = offset;
	offset = (s1_len - 1 + (!s1_len));
	while (offset && ft_strchr(set, s1[offset]) && count++ >= 0)
		offset--;
	return (ft_substr(s1, start, (s1_len - count)));
}

char	*ft_strstrim(char const *s1, char sep)
{
	char	*res;
	size_t	s1_len;
	size_t	count;
	int		offset;
	int		start;

	if (s1 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	offset = 0;
	count = 0;
	while (s1[offset] && s1[offset] == sep && count++ >= 0)
		offset++;
	start = offset;
	offset = (s1_len - 1 + (!s1_len));
	while (offset && s1[offset] == sep && count++ >= 0)
		offset--;
	res = ft_substr(s1, start, (s1_len - count));
	if (res == NULL)
		return (NULL);
	return (res);
}
