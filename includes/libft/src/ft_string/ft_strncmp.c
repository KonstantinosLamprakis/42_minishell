/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:09:13 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:35:49 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	if (n == 0)
		return (0);
	index = 0;
	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	while (uc_s1[index] && uc_s1[index] == uc_s2[index] && index + 1 < n)
		index++;
	return (uc_s1[index] - uc_s2[index]);
}
