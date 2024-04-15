/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:34:08 by lgreau            #+#    #+#             */
/*   Updated: 2024/03/10 16:10:02 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag	*t_flag_new(void)
{
	t_flag	*flag;

	flag = malloc(sizeof(t_flag));
	if (!flag)
		return (flag);
	ft_reset_flag(flag);
	return (flag);
}

void	ft_reset_flag(t_flag *flag)
{
	flag->f_offset = 0;
	flag->alt = 0;
	flag->la_flag = 0;
	flag->sign = 0;
	flag->spc = 0;
	flag->zero = 0;
	flag->fw_v = 0;
	flag->p_flag = 0;
	flag->p_v = 0;
}
