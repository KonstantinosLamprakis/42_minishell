/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:34 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 14:53:13 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include "../ft_string/ft_string.h" /* ft_strjoinline, ft_strlen, ft_strchr
										ft_strstrim	*/
# include "../ft_memory/ft_memory.h" // ft_memmove

# include <stdlib.h> // malloc & free
# include <unistd.h> // read
# include <limits.h> //	OPEN_MAX : max amount of open files

/*	Preprocessor Options -D<macroname>=<value>
	Adds  an  implicit  #define  into the predefines buffer
	which is read before the source file is
	preprocessed.

	-DBUFFER_SIZE=<value>	<=>		# define BUFFER_SIZE value
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*ft_get_next_line(int fd);
char	*init_line(char *buffer);
char	*read_line(int fd, char *buffer, int *r_len);
char	*place_next(char *buffer);
int		read_buffer(int fd, char *buf);
int		fs(void *ptr, char **buffer, int fd);

char	*ft_get_next_line_nonl(int fd);

#endif
