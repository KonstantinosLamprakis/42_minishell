/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:06:29 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 16:52:02 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "../ft_printf/ft_printf.h"
# include <stdio.h>  // __func__
# include <stdlib.h> // NULL

typedef enum e_errno
{
	NO_ERROR,
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
	NO_SUCH_FILE_OR_DIR,
	INVALID_OPT,
	ENV_NOT_SET,
	INVALID_IDENTIFIER,
	ERR_COUNT
}				t_errno;

# define INVALID_ARG_ERR "invalid argument "
# define ALLOC_ERR "error allocating memory "
# define OPEN_ERR "error opening a file "
# define CLOSE_ERR "error closing a file "
# define READ_ERR "error reading the file "
# define WRONG_ERRNO_ERR "wrong error number "
# define BITMAP_MASK_ERR "wrong number of bits to create the mask "
# define QUEUE_AT_CAPACITY_ERR "queue is overpopulated "
# define QUEUE_EMPTY_ERR "queue is empty "
# define SYNTAX_ERR "syntax error "
# define DUP_ERR "error dupliacting file descriptors "
# define FORK_ERR "error forking "
# define COMMAND_NOT_FOUND_ERR "command not found "
# define NO_SUCH_FILE_OR_DIR_ERR "no such file or directory "
# define INVALID_OPT_ERR "invalid option "
# define ENV_NOT_SET_ERR "not set "
# define INVALID_IDENTIFIER_ERR "not valid identifier "

int				*get_errno(void);
void			set_errno(int err_value);

char			**get_error_caller(void);
void			set_error_caller(char *caller_name);

char			**get_strerror(void);
char			*ft_strerror(int ft_errno);
void			ft_perror(void);

void			set_error(char *caller_name, int ft_errno);

#endif
