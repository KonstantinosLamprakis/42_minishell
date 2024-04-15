/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:19:13 by lgreau            #+#    #+#             */
/*   Updated: 2024/03/10 16:11:37 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_flag1(va_list ap, const char *str, t_flag *flag)
{
	if (*str == '#' && flag->f_offset++ >= 0)
	{
		flag->alt = 1;
		return (ft_parse_flag1(ap, str + 1, flag));
	}
	if (*str == ' ' && flag->f_offset++ >= 0)
	{
		flag->spc = 1;
		return (ft_parse_flag1(ap, str + 1, flag));
	}
	if (*str == '+' && flag->f_offset++ >= 0)
	{
		flag->sign = 1;
		return (ft_parse_flag1(ap, str + 1, flag));
	}
	return (ft_parse_flag2(ap, str, flag));
}

int	ft_parse_flag2(va_list ap, const char *str, t_flag *flag)
{
	if (*str == '-' && flag->f_offset++ >= 0)
	{
		flag->la_flag = 1;
		return (ft_parse_flag1(ap, str + 1, flag));
	}
	if (*str == '0' && flag->f_offset++ >= 0)
	{
		flag->zero = 1;
		return (ft_parse_flag1(ap, str + 1, flag));
	}
	return (ft_parse_width(ap, str, flag));
}
