/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:46:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 10:39:17 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

/**
 * @brief Creates a bitmap mask from the given arguments
 *
 * @param len Nb of arguments given
 * @param ... Individual uint32 values to create the mask from
 * @return uint32_t ft_bitmap compatible mask
 */
// u_int32_t: for linux
// uint32_t: for MAC
u_int32_t	ft_mask(int len, ...)
{
	u_int32_t	mask;
	va_list		ap;
	int			offset;

	if (len > 32 || len < 0)
		return (set_error((char *)__func__, BITMAP_MASK), 0);
	mask = 0;
	va_start(ap, len);
	offset = -1;
	while (++offset < len)
		mask |= va_arg(ap, int);
	va_end(ap);
	return (mask);
}
