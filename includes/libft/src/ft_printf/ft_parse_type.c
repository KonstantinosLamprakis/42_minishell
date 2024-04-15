/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:20:30 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:33:12 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_type(va_list ap, const char *str, t_flag *flag)
{
	if (*str == 'c' && flag->f_offset++ >= 0)
		return (ft_printchar(va_arg(ap, int), flag));
	if (*str == 's' && flag->f_offset++ >= 0)
		return (ft_printstr(va_arg(ap, char *), flag));
	if (*str == 'p' && flag->f_offset++ >= 0)
		return (ft_printptr((size_t)va_arg(ap, void *), flag));
	if (*str == 'd' && flag->f_offset++ >= 0)
		return (ft_printnbr(va_arg(ap, int), flag));
	if (*str == 'i' && flag->f_offset++ >= 0)
		return (ft_printnbr(va_arg(ap, int), flag));
	if (*str == 'u' && flag->f_offset++ >= 0)
		return (ft_printunbr(va_arg(ap, unsigned int), flag));
	if (*str == 'x' && flag->f_offset++ >= 0)
		return (ft_printhex(va_arg(ap, int), flag, 1));
	if (*str == 'X' && flag->f_offset++ >= 0)
		return (ft_printhex(va_arg(ap, int), flag, 0));
	if (*str == '%' && flag->f_offset++ >= 0)
		return (ft_printchar('%', flag));
	return (0);
}
