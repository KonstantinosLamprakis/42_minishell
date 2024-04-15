/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:14:48 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:19:29 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

int	ft_putstr(char *str)
{
	return (ft_putstr_fd(str, 1));
}

int	ft_putstr_fd(char *str, int fd)
{
	if (!str && write(fd, "(null)", 6) >= 0)
		return (6);
	write(fd, str, ft_strlen(str));
	return (ft_strlen(str));
}
