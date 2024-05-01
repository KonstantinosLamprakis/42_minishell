/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 08:41:23 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

char	**get_strerror(void)
{
	static char	*error_messages[ERR_COUNT];

	error_messages[INVALID_ARG] = INVALID_ARG_ERR;
	error_messages[ALLOC] = ALLOC_ERR;
	error_messages[OPEN] = OPEN_ERR;
	error_messages[CLOSE] = CLOSE_ERR;
	error_messages[READ] = READ_ERR;
	error_messages[WRONG_ERRNO] = WRONG_ERRNO_ERR;
	error_messages[BITMAP_MASK] = BITMAP_MASK_ERR;
	error_messages[QUEUE_AT_CAPACITY] = QUEUE_AT_CAPACITY_ERR;
	error_messages[QUEUE_EMPTY] = QUEUE_EMPTY_ERR;
	error_messages[SYNTAX] = SYNTAX_ERR;
	error_messages[DUP] = DUP_ERR;
	error_messages[FORK] = FORK_ERR;
	error_messages[COMMAND_NOT_FOUND] = COMMAND_NOT_FOUND_ERR;
	error_messages[NO_SUCH_FILE_OR_DIR] = NO_SUCH_FILE_OR_DIR_ERR;
	error_messages[INVALID_OPT] = INVALID_OPT_ERR;
	error_messages[ENV_NOT_SET] = ENV_NOT_SET_ERR;
	error_messages[INVALID_IDENTIFIER] = INVALID_IDENTIFIER_ERR;
	return (error_messages);
}

char	*ft_strerror(int ft_errno)
{
	char	**error_messages;

	if (ft_errno < 0 || ft_errno >= ERR_COUNT)
		return (set_error((char *)__func__, WRONG_ERRNO), NULL);
	error_messages = get_strerror();
	return (error_messages[ft_errno]);
}

void	ft_perror(void)
{
	int		ft_errno;
	char	*error_message;
	char	*caller_name;

	ft_errno = *get_errno();
	error_message = ft_strerror(ft_errno);
	caller_name = *get_error_caller();
	ft_printf("%s%s\n", error_message, caller_name);
}
