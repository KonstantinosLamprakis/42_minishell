/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:39:02 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 15:50:56 by klamprak         ###   ########.fr       */
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
	cmd = ft_escsplit(token->str, ft_iswspace, ft_isquote);
	if (!cmd)
		return (-1);
	exec_cmd(cmd);
	free_arr(cmd, 1);
	return (-1);
}

void	exec_cmd(char **cmd_args)
{
	t_program	*program;
	pid_t		child;
	char		*cmd;

	if (!is_builtin(cmd_args[0]))
		cmd = get_cmd(cmd_args);
	else
		cmd = cmd_args[0];
	if (!cmd)
		return ;
	program = get_program();
	child = fork();
	if (child < 0)
		return (set_error((char *)__func__, FORK));
	if (child == CHILD_PROCESS)
	{
		if (put_signal_handler(0, SIGINT) || put_signal_handler(0, SIGQUIT))
		{
			printf("Error: handling signals\n");
			return ;
		}
		if (!is_builtin(cmd_args[0]))
			execve(cmd, cmd_args, program->envp);
		else
			get_program()->status = builtin_execve(cmd, cmd_args, program->envp);
		exit(get_program()->status);
	}
	waitpid(child, &program->status, 0);
	if (!is_builtin(cmd_args[0]))
		free(cmd);
	if (is_builtin(cmd_args[0]) == 2)
		exit (get_program()->status);
	//printf("Return status: %d\n", program->status);
}
