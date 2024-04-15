/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:43:59 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:31:53 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_char(int c, t_flag *flag)
{
	int	len;
	int	index;

	len = 0;
	index = flag->fw_v - 1;
	while (index-- > 0)
	{
		if (flag->zero && len++ >= 0)
			write(1, "0", 1);
		else if (!flag->zero && len++ >= 0)
			write(1, " ", 1);
	}
	write(1, &c, 1);
	return (len + 1);
}

static int	handle_char_la(int c, t_flag *flag)
{
	int	len;
	int	index;

	len = 1;
	write(1, &c, 1);
	index = flag->fw_v - 1;
	while (index-- > 0 && len++ >= 0)
		write(1, " ", 1);
	return (len);
}

int	ft_printchar(int c, t_flag *flag)
{
	int	len;

	len = 0;
	if (!flag->la_flag)
		len += handle_char(c, flag);
	else
		len += handle_char_la(c, flag);
	return (len);
}
