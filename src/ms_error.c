/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:28:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 14:14:57 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_perror(char *arg, int ft_errno)
{
	t_program	*program;
	char		*tmp;

	set_errno(ft_errno);
	if (errno != NO_ERROR)
	{
		program = get_program();
		tmp = strerror(errno);
		write(STDERR, ERROR_PROMPT, ft_strlen(ERROR_PROMPT));
		ft_putstr_fd(": ", STDERR);
		write(STDERR, arg, ft_strlen(arg));
		ft_putstr_fd(": ", STDERR);
		write(STDERR, tmp, ft_strlen(tmp));
		write(STDERR, "\n", 1);
	}
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
