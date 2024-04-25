/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:39:02 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/25 10:36:53 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char **cmd_args)
{
	t_program	*program;
	char		*cmd;
	int			index;

	program = get_program();
	if (cmd_args[0][0] == '/')
	{
		if (access(cmd_args[0], F_OK) >= 0)
			return (cmd_args[0]);
	}
	else
	{
		index = -1;
		while (program->env_path[++index])
		{
			cmd = ft_strjoin_3(program->env_path[index], "/", cmd_args[0]);
			if (access(cmd, F_OK) >= 0)
				return (cmd);
			free(cmd);
		}
	}
	return (set_error((char *)__func__, COMMAND_NOT_FOUND), NULL);
}

int	cmd_handler(void *arg)
{
	t_token	*token;
	char	**cmd;

	token = (t_token *)arg;
	printf("\n%s: received token:\n", (char *)__func__);
	printf("  |- string: %s\n", token->str);
	cmd = ft_escsplit(token->str, ft_iswspace, ft_isquote);
	printf("  |- cmd:\n");
	if (cmd)
	{
		int	i = -1;
		while (cmd[++i])
			printf("    |- cmd[%d] = %s\n", i, cmd[i]);
	}
	printf("\n");
	exec_cmd(cmd);
	// free_arr(cmd, 1);
	return (-1);
}

void	exec_cmd(char **cmd_args)
{
	t_program	*program;
	pid_t		child;
	char		*cmd;

	cmd = get_cmd(cmd_args);
	if (!cmd)
		return (set_error((char *)__func__, INVALID_ARG));
	program = get_program();
	child = fork();
	if (child < 0)
		return (set_error((char *)__func__, FORK));
	if (child == CHILD_PROCESS)
		execve(cmd, cmd_args, program->envp);
	waitpid(child, &program->status, 0);
	printf("Return status: %d\n", program->status);
}
