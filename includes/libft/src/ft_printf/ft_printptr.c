/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:36:33 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:29:59 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	Without la_flag	*/
static int	handle_hexnbr(char *str, t_flag *flag, int lower)
{
	int	len;
	int	index;

	len = 0;
	index = flag->fw_v - 2 * flag->alt - ft_max_int(2, ft_strlen(str),
			flag->p_v);
	while (index-- > 0)
	{
		if (flag->zero && !flag->p_v && len++ >= 0)
			write(1, "0", 1);
		else if ((flag->p_v || !flag->zero) && len++ >= 0)
			write(1, " ", 1);
	}
	len += 2 * flag->alt;
	if (flag->alt && lower)
		write(1, "0x", 2);
	else if (flag->alt && !lower)
		write(1, "0X", 2);
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

	len = 2 * flag->alt;
	if (flag->alt && lower)
		write(1, "0x", 2);
	else if (flag->alt && !lower)
		write(1, "0X", 2);
	index = flag->p_v - ft_strlen(str);
	while (index-- > 0 && len++ >= 0)
		write(1, "0", 1);
	len += ft_putstr(str);
	index = flag->fw_v - 2 * flag->alt - ft_max_int(2, ft_strlen(str),
			flag->p_v);
	while (index-- > 0 && len++ >= 0)
		write(1, " ", 1);
	return (len);
}

int	ft_printptr(size_t n, t_flag *flag)
{
	char	*str;
	int		len;

	str = ft_lhtoa(n);
	if (str == NULL)
		return (-1);
	len = 0;
	flag->alt = 1;
	if (!flag->la_flag)
		len += handle_hexnbr(str, flag, 1);
	else
		len += handle_hexnbr_la(str, flag, 1);
	free(str);
	return (len);
}
