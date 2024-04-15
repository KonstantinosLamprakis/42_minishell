/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:21:44 by lgreau            #+#    #+#             */
/*   Updated: 2024/03/09 12:26:23 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_width(va_list ap, const char *str, t_flag *flag)
{
	if ((*str >= '1' && *str <= '9') && flag->f_offset++ >= 0)
	{
		flag->fw_v = flag->fw_v * 10 + (*str++ - '0');
		while (ft_isdigit(*str) && flag->f_offset++ >= 0)
			flag->fw_v = flag->fw_v * 10 + (*str++ - '0');
		return (ft_parse_precision(ap, str, flag));
	}
	if (*str == '*' && flag->f_offset++ >= 0)
	{
		flag->fw_v = va_arg(ap, int);
		return (ft_parse_precision(ap, str + 1, flag));
	}
	else
		return (ft_parse_precision(ap, str, flag));
}
