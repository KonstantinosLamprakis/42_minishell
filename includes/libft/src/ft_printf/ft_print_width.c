/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:41:48 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:33:44 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_width(t_flag *flag)
{
	if (flag->zero && !flag->p_v)
	{
		write(1, "0", 1);
		return (1);
	}
	else if (flag->p_v || !flag->zero)
	{
		write(1, " ", 1);
		return (1);
	}
	return (0);
}
