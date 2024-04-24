/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:06:29 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 08:00:16 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "../ft_printf/ft_printf.h"
# include <stdio.h>  // __func__
# include <stdlib.h> // NULL

typedef enum e_errno
{
	INVALID_ARG,
	ALLOC,
	OPEN,
	CLOSE,
	READ,
	WRONG_ERRNO,
	BITMAP_MASK,
	QUEUE_AT_CAPACITY,
	QUEUE_EMPTY,
	SYNTAX,
	DUP,
	FORK,
	COMMAND_NOT_FOUND,
	ERR_COUNT
}				t_errno;

# define INVALID_ARG_ERR "Invalid argument: "
# define ALLOC_ERR "Error allocating memory: "
# define OPEN_ERR "Error opening a file: "
# define CLOSE_ERR "Eroor closing a file: "
# define READ_ERR "Error reading the file: "
# define WRONG_ERRNO_ERR "Wrong error number: "
# define BITMAP_MASK_ERR "Wrong number of bits to create the mask: "
# define QUEUE_AT_CAPACITY_ERR "Queue is overpopulated: "
# define QUEUE_EMPTY_ERR "Queue is empty: "
# define SYNTAX_ERR "Syntax error: "
# define DUP_ERR "Error dupliacting file descriptors: "
# define FORK_ERR "Error forking: "
# define COMMAND_NOT_FOUND_ERR "Command not found: "

int				*get_errno(void);
void			set_errno(int err_value);

char			**get_error_caller(void);
void			set_error_caller(char *caller_name);

char			**get_strerror(void);
char			*ft_strerror(int ft_errno);
void			ft_perror(void);

void			set_error(char *caller_name, int ft_errno);

#endif
