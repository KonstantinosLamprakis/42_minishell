/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:20:15 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 11:40:37 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_opened_files(void)
{
	t_program	*program;
	int			index;

	program = get_program();
	index = -1;
	while (++index >= 0 && program->opened_count > 0)
	{
		if (index == 0 || program->opened_files[index] != 0)
		{
			close(index);
			program->opened_count--;
		}
	}
}

void	reset_std_fd(void)
{
	t_program	*program;
	int			index;

	program = get_program();
	index = -1;
	while (++index < STDCOUNT)
		if (dup2(program->std_fd[index], index) < 0)
			return (set_error((char *)__func__, DUP));
}

/**
 * @brief Resets the structure for the next command line
 * Closes all opened files and puts back the stdin/out/err as fd 0/1/2
 */
void	reset_struct(void)
{
	// close_opened_files();
	reset_std_fd();
	if (*get_errno() == SYNTAX)
		set_status(SYNTAX_STATUS);
	else if (*get_errno() == COMMAND_NOT_FOUND)
		set_status(CMD_NF_STATUS);
	else if (*get_errno() == NO_SUCH_FILE_OR_DIR)
		set_status(NO_FD_STATUS);
	set_errno(NO_ERROR);
}
