/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:58:47 by lgreau            #+#    #+#             */
/*   Updated: 2024/03/10 16:58:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_intlog_a(int n, int a)
{
	int	log;

	if (n == 0)
		return (1);
	log = 0;
	while (n != 0 && log++ >= 0)
		n /= a;
	return (log);
}

int	ft_max_int(int argc, ...)
{
	va_list	ap;
	int		max;
	int		arg;

	va_start(ap, argc);
	max = INT_MIN;
	while (argc--)
	{
		arg = va_arg(ap, int);
		max = (max * (max > arg) + arg * (max <= arg));
	}
	va_end(ap);
	return (max);
}

int	ft_min_int(int argc, ...)
{
	va_list	ap;
	int		min;
	int		arg;

	va_start(ap, argc);
	min = INT_MAX;
	while (argc--)
	{
		arg = va_arg(ap, int);
		min = (min * (min < arg) + arg * (min >= arg));
	}
	va_end(ap);
	return (min);
}
