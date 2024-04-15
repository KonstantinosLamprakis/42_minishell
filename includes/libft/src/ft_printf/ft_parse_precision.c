/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:37:03 by lgreau            #+#    #+#             */
/*   Updated: 2024/03/10 17:19:26 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_parse_precision(va_list ap, const char *str, t_flag *flag)
{
	if (*str == '.' && flag->f_offset++ >= 0)
	{
		str++;
		flag->p_flag = 1;
		if ((*str >= '0' && *str <= '9') && flag->f_offset++ >= 0)
		{
			flag->p_v = flag->p_v * 10 + (*str++ - '0');
			while (ft_isdigit(*str) && flag->f_offset++ >= 0)
				flag->p_v = flag->p_v * 10 + (*str++
						- '0');
			return (ft_parse_type(ap, str, flag));
		}
		else if (*str == '*' && flag->f_offset++ >= 0)
		{
			flag->p_v = va_arg(ap, int);
			return (ft_parse_type(ap, str + 1, flag));
		}
	}
	return (ft_parse_type(ap, str, flag));
}
