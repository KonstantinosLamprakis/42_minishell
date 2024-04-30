/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:28:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 13:49:49 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_perror(char *arg, int ft_errno)
{
	set_errno(ft_errno);
	if (errno != NO_ERROR)
		printf("%s: %s: %s\n", ERROR_PROMPT, arg, strerror(errno));
}

void	ms_syntax_error(char *arg)
{
	set_status(SYNTAX_STATUS);
	set_errno(SYNTAX);
	printf("%s: ", ERROR_PROMPT);
	printf("%s `%s'\n", SYNTAX_ERR_MSG, arg);
}

void	ms_cmdnf_error(char *arg)
{
	set_status(CMD_NF_STATUS);
	set_errno(COMMAND_NOT_FOUND);
	printf("%s: ", ERROR_PROMPT);
	printf("%s: %s\n", arg, CMD_NF_ERR_MSG);
}
