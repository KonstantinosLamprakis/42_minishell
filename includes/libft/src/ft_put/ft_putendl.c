/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:17:48 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:03:17 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

int	ft_putendl_fd(char *str, int fd)
{
	return (ft_putstr_fd(str, fd), write(fd, "\n", 1), ft_strlen(str) + 1);
}

int	ft_putendl(char *str)
{
	return (ft_putendl_fd(str, 1));
}
