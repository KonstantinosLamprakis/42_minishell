/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_nonl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:45:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:53:00 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

char	*ft_get_next_line_nonl(int fd)
{
	char	*line;
	char	*trimmed;

	line = ft_get_next_line(fd);
	if (!line)
		return (NULL);
	if (!ft_strchr(line, '\n'))
		return (line);
	trimmed = ft_strstrim(line, '\n');
	return (free(line), trimmed);
}
