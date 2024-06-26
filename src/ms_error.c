/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:28:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 17:40:19 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_perror(char *arg, int ft_errno)
{
	char		*tmp;

	set_errno(ft_errno);
	if (errno != NO_ERROR)
	{
		tmp = strerror(errno);
		if (errno == 2)
			set_status(NO_FD_STATUS);
		write(STDERR, ERROR_PROMPT, ft_strlen(ERROR_PROMPT));
		ft_putstr_fd(": ", STDERR);
		write(STDERR, arg, ft_strlen(arg));
		ft_putstr_fd(": ", STDERR);
		write(STDERR, tmp, ft_strlen(tmp));
		write(STDERR, "\n", 1);
	}
}

void	ms_perror_custom(char *arg, char *msg, int ft_errno)
{
	char		*tmp;

	set_errno(ft_errno);
	write(STDERR, ERROR_PROMPT, ft_strlen(ERROR_PROMPT));
	ft_putstr_fd(": ", STDERR);
	write(STDERR, arg, ft_strlen(arg));
	ft_putstr_fd(": ", STDERR);
	write(STDERR, msg, ft_strlen(msg));
	ft_putstr_fd(" ", STDERR);
	if (*get_errno() != NO_ERROR)
	{
		tmp = get_strerror()[*get_errno()];
		write(STDERR, tmp, ft_strlen(tmp));
	}
	write(STDERR, "\n", 1);
}

void	ms_syntax_error(char *arg)
{
	set_status(SYNTAX_STATUS);
	set_errno(SYNTAX);
	write(STDERR, ERROR_PROMPT, ft_strlen(ERROR_PROMPT));
	ft_putstr_fd(": ", STDERR);
	write(STDERR, SYNTAX_ERR_MSG, ft_strlen(SYNTAX_ERR_MSG));
	ft_putstr_fd(" `", STDERR);
	write(STDERR, arg, ft_strlen(arg));
	ft_putstr_fd("'\n", STDERR);
}

void	ms_no_such_fd_error(char *arg)
{
	set_status(NO_FD_STATUS);
	set_errno(NO_SUCH_FILE_OR_DIR);
	write(STDERR, ERROR_PROMPT, ft_strlen(ERROR_PROMPT));
	ft_putstr_fd(": ", STDERR);
	write(STDERR, arg, ft_strlen(arg));
	ft_putstr_fd(": ", STDERR);
	write(STDERR, NO_FD_ERR_MSG, ft_strlen(NO_FD_ERR_MSG));
	ft_putstr_fd("\n", STDERR);
}

void	ms_cmdnf_error(char *arg)
{
	set_status(CMD_NF_STATUS);
	set_errno(COMMAND_NOT_FOUND);
	write(STDERR, ERROR_PROMPT, ft_strlen(ERROR_PROMPT));
	ft_putstr_fd(": ", STDERR);
	write(STDERR, arg, ft_strlen(arg));
	ft_putstr_fd(": ", STDERR);
	write(STDERR, CMD_NF_ERR_MSG, ft_strlen(CMD_NF_ERR_MSG));
	ft_putstr_fd("\n", STDERR);
}
