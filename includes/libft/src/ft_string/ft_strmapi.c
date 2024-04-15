/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:51:45 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:35:47 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	index;
	size_t			s_len;

	index = 0;
	s_len = ft_strlen(s);
	res = malloc((s_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (index < s_len)
	{
		res[index] = (*f)(index, s[index]);
		index++;
	}
	res[index] = '\0';
	return (res);
}
