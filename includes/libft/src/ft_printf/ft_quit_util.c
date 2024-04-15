/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:04:23 by lgreau            #+#    #+#             */
/*   Updated: 2024/03/09 01:07:55 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_va_quit(va_list ap)
{
	va_end(ap);
	return (1);
}

int	ft_free_flag(t_flag *flag)
{
	free(flag);
	return (1);
}
