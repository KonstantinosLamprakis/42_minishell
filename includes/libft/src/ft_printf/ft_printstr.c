/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:57:48 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:30:54 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_str(char *s, t_flag *flag)
{
	int	len;
	int	index;
	int	offset;

	len = 0;
	if (!flag->p_flag)
		index = flag->fw_v - ft_strlen(s);
	else
		index = flag->fw_v - ft_min_int(2, ft_strlen(s), flag->p_v);
	while (index-- > 0)
	{
		if (flag->zero && len++ >= 0)
			write(1, "0", 1);
		else if (!flag->zero && len++ >= 0)
			write(1, " ", 1);
	}
	if (!flag->p_flag)
		index = ft_strlen(s);
	else
		index = ft_min_int(2, ft_strlen(s), flag->p_v);
	offset = 0;
	while (index-- > 0 && len++ >= 0)
		write(1, (s + offset++), 1);
	return (len);
}

static int	handle_str_la(char *s, t_flag *flag)
{
	int	len;
	int	index;
	int	offset;

	len = 0;
	if (!flag->p_flag)
		index = ft_strlen(s);
	else
		index = ft_min_int(2, ft_strlen(s), flag->p_v);
	offset = 0;
	while (index-- > 0 && len++ >= 0)
		write(1, (s + offset++), 1);
	index = flag->fw_v - len;
	while (index-- > 0 && len++ >= 0)
		write(1, " ", 1);
	return (len);
}

static int	handle_null(t_flag *flag)
{
	int	len;
	int	index;
	int	offset;

	len = 0;
	if (!flag->p_flag)
		index = flag->fw_v - 6;
	else
		index = flag->fw_v - ft_min_int(2, 6, flag->p_v);
	while (index-- > 0)
	{
		if (flag->zero && len++ >= 0)
			write(1, "0", 1);
		else if (!flag->zero && len++ >= 0)
			write(1, " ", 1);
	}
	if (!flag->p_flag)
		index = 6;
	else
		index = ft_min_int(2, 6, flag->p_v);
	offset = 0;
	while (index-- > 0 && len++ >= 0)
		write(1, &("(null)"[offset++]), 1);
	return (len);
}

static int	handle_null_la(t_flag *flag)
{
	int	len;
	int	index;
	int	offset;

	len = 0;
	if (!flag->p_flag)
		index = 6;
	else
		index = ft_min_int(2, 6, flag->p_v);
	offset = 0;
	while (index-- > 0 && len++ >= 0)
		write(1, &("(null)"[offset++]), 1);
	index = flag->fw_v - len;
	while (index-- > 0 && len++ >= 0)
		write(1, " ", 1);
	return (len);
}

int	ft_printstr(char *s, t_flag *flag)
{
	int	len;

	len = 0;
	if (!flag->la_flag && s != NULL)
		len += handle_str(s, flag);
	else if (!flag->la_flag && s == NULL)
		len += handle_null(flag);
	else if (flag->la_flag && s != NULL)
		len += handle_str_la(s, flag);
	else if (flag->la_flag && s == NULL)
		len += handle_null_la(flag);
	return (len);
}
