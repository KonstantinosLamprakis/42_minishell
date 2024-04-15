/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:02:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:41:56 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_putprefix(t_flag *flag, int lower, int condition)
{
	if (condition && flag->alt && lower)
	{
		write(1, "0x", 2);
		return (2);
	}
	else if (condition && flag->alt && !lower)
	{
		write(1, "0X", 2);
		return (2);
	}
	return (0);
}

/*	Without la_flag	*/
static int	handle_hexnbr(char *str, t_flag *flag, int lower)
{
	int	len;
	int	index;

	len = hex_putprefix(flag, lower, (flag->zero && !flag->p_flag
				&& (*str != '0')));
	index = flag->fw_v - 2 * (flag->alt) * (*str != '0') - ft_max_int(2,
			ft_strlen(str), flag->p_v);
	while (index-- > 0)
	{
		if (flag->zero && !flag->p_v && len++ >= 0)
			write(1, "0", 1);
		else if ((flag->p_v || !flag->zero) && len++ >= 0)
			write(1, " ", 1);
	}
	len += hex_putprefix(flag, lower, ((flag->p_flag || !flag->zero)
				&& (*str != '0')));
	index = flag->p_v - ft_strlen(str);
	while (index-- > 0 && len++ >= 0)
		write(1, "0", 1);
	return (len + ft_putstr(str));
}

/*	With la_flag	*/
static int	handle_hexnbr_la(char *str, t_flag *flag, int lower)
{
	int	len;
	int	index;

	len = 2 * flag->alt * (*str != '0');
	if (*str != '0' && flag->alt && lower)
		write(1, "0x", 2);
	else if (*str != '0' && flag->alt && !lower)
		write(1, "0X", 2);
	index = flag->p_v - ft_strlen(str);
	while (index-- > 0 && len++ >= 0)
		write(1, "0", 1);
	len += ft_putstr(str);
	index = flag->fw_v - 2 * flag->alt * (*str != '0') - ft_max_int(2,
			ft_strlen(str), flag->p_v);
	while (index-- > 0 && len++ >= 0)
		write(1, " ", 1);
	return (len);
}

int	ft_printhex(unsigned int n, t_flag *flag, int lower)
{
	char	*str;
	int		len;

	str = ft_htoa(n, lower);
	if (str == NULL)
		return (-1);
	len = 0;
	if (*str == '0' && flag->p_flag && flag->p_v == 0 && len++ >= 0)
	{
		while (flag->fw_v-- > 0)
			len += ft_print_width(flag);
		return (0);
	}
	if (!flag->la_flag)
		len += handle_hexnbr(str, flag, lower);
	else
		len += handle_hexnbr_la(str, flag, lower);
	free(str);
	return (len);
}
