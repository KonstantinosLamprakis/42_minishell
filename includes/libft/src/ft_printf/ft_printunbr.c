/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:46:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:41:46 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_unbr(char *str, t_flag *flag)
{
	int	len;
	int	index;

	len = 0;
	index = flag->fw_v - (flag->spc || flag->sign) - ft_max_int(2,
			ft_strlen(str), flag->p_v);
	while (index-- > 0)
	{
		if (flag->zero && !flag->p_v && len++ >= 0)
			write(1, "0", 1);
		else if ((flag->p_v || !flag->zero) && len++ >= 0)
			write(1, " ", 1);
	}
	if (flag->sign && len++ >= 0)
		write(1, "+", 1);
	else if (flag->spc && len++ >= 0)
		write(1, " ", 1);
	index = flag->p_v - ft_strlen(str);
	while (index-- > 0 && len++ >= 0)
		write(1, "0", 1);
	return (len + ft_putstr(str));
}

static int	handle_unbr_la(char *str, t_flag *flag)
{
	int	len;
	int	index;

	len = 0;
	if (flag->sign && len++ >= 0)
		write(1, "+", 1);
	else if (flag->spc && len++ >= 0)
		write(1, " ", 1);
	index = flag->p_v - ft_strlen(str);
	while (index-- > 0 && len++ >= 0)
		write(1, "0", 1);
	len += ft_putstr(str);
	index = flag->fw_v - (flag->sign || flag->spc) - ft_max_int(2,
			ft_strlen(str), flag->p_v);
	while (index-- > 0 && len++ >= 0)
		write(1, " ", 1);
	return (len);
}

int	ft_printunbr(unsigned int n, t_flag *flag)
{
	int		len;
	char	*str;

	str = ft_utoa(n);
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
		len += handle_unbr(str, flag);
	else
		len += handle_unbr_la(str, flag);
	free(str);
	return (len);
}
