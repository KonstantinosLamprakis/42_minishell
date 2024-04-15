/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:34:28 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:44:54 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

int	fs(void *ptr, char **buffer, int fd)
{
	if (fd < 0)
		free(ptr);
	else
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (1);
}
