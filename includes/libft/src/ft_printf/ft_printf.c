/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:09:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/03/10 17:10:13 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(va_list ap, char *str, t_flag *flag)
{
	int	len;

	len = 0;
	if (*str == '%')
	{
		len = ft_parse_flag1(ap, str + 1, flag);
		if (len < 0 && ft_va_quit(ap) && ft_free_flag(flag))
			return (-1);
	}
	else if (*str != '%' && len++ >= 0)
		write(1, str, 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		len;
	int		offset;
	t_flag	*flag;

	va_start(ap, str);
	len = 0;
	offset = 0;
	flag = t_flag_new();
	if (!flag)
		return (0);
	while (*str)
	{
		offset = handle_format(ap, (char *)str, flag);
		if (offset < 0)
			return (0);
		len += offset;
		str += flag->f_offset;
		ft_reset_flag(flag);
		str++;
	}
	ft_va_quit(ap);
	ft_free_flag(flag);
	return (len);
}
