/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:00:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 10:12:34 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	count;
	int		offset;
	int		start;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	offset = 0;
	count = 0;
	while (s1[offset] && ft_strchr(set, s1[offset]) && ++count)
		offset++;
	start = offset;
	offset = (s1_len - 1 + (!s1_len));
	while (offset && ft_strchr(set, s1[offset]) && ++count)
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
	while (s1[offset] && s1[offset] == sep && ++count)
		offset++;
	start = offset;
	offset = (s1_len - 1 + (!s1_len));
	while (offset && s1[offset] == sep && ++count)
		offset--;
	res = ft_substr(s1, start, (s1_len - count));
	if (res == NULL)
		return (NULL);
	return (res);
}
