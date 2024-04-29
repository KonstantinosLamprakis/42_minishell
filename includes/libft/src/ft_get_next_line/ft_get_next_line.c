/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:14 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 10:39:53 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

int	read_buffer(int fd, char *buf)
{
	int	r_len;

	r_len = read(fd, buf, BUFFER_SIZE);
	if (r_len >= 0)
		buf[r_len] = 0;
	return (r_len);
}

char	*init_line(char *buf)
{
	char	*line;
	int		b_len;
	int		is_nl;

	if (!buf)
		return (NULL);
	b_len = 0;
	while (buf[b_len] && buf[b_len] != '\n')
		b_len++;
	is_nl = (buf[b_len] != 0);
	line = malloc((b_len + 1 + is_nl) * sizeof(char));
	if (!line)
		return (NULL);
	line = ft_memmove(line, buf, b_len + is_nl);
	line[b_len + is_nl] = 0;
	return (line);
}

char	*read_line(int fd, char *buf, int *r_len)
{
	char	*line;
	char	*tmp;

	line = init_line(buf);
	if (!line)
		return (NULL);
	if (ft_strchr(line, '\n') != NULL)
		return (line);
	*r_len = read_buffer(fd, buf);
	if (*r_len < 0)
		return (NULL);
	while (*r_len > 0)
	{
		tmp = ft_strjoinline(line, buf, *r_len);
		if ((!tmp && fs(line, NULL, -1)) || (!fs(line, NULL, -1)))
			return (NULL);
		line = tmp;
		if (ft_strchr(line, '\n') != NULL)
			return (line);
		*r_len = read_buffer(fd, buf);
		if (*r_len < 0)
			return (NULL);
	}
	return (line);
}

char	*place_next(char *buf)
{
	char	*eol;
	size_t	eol_len;

	if (!buf)
		return (NULL);
	eol = ft_strchr(buf, '\n');
	if (eol != NULL)
	{
		eol_len = ft_strlen(eol + 1);
		buf = ft_memmove(buf, eol + 1, eol_len + 1);
		buf[eol_len] = 0;
		return (buf);
	}
	return (NULL);
}

// FOPEN_MAX: for linux
// OPEN_MAX: for MAC
char	*ft_get_next_line(int fd)
{
	static char	*buf[FOPEN_MAX];
	char		*line;
	int			r_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0 && fs(NULL, buf, fd)))
		return (NULL);
	r_len = 1;
	if (!buf[fd])
	{
		buf[fd] = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf[fd])
			return (NULL);
		r_len = read(fd, buf[fd], BUFFER_SIZE);
		if (r_len <= 0 && fs(NULL, buf, fd))
			return (NULL);
		buf[fd][r_len] = 0;
	}
	line = read_line(fd, buf[fd], &r_len);
	if ((!line || r_len < 0) && fs(NULL, buf, fd))
		return (NULL);
	if (ft_strchr(line, '\n') != NULL || (r_len == 0 && !fs(NULL, buf, fd)))
		buf[fd] = place_next(buf[fd]);
	if (ft_strlen(line) == 0 && fs(line, NULL, -1))
		return (NULL);
	return (line);
}
