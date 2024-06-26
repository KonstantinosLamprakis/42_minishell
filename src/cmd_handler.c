/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:39:02 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 18:12:11 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_cmd_path(char *str)
{
	if (str[0] == '.' && (ft_strlen(str) <= 1 || str[1] == '.'))
		return (0);
	return (1);
}

char	*get_cmd(char **cmd_args)
{
	t_program	*program;
	char		*cmd;
	int			index;

	program = get_program();
	if (cmd_args[0][0] == '/')
	{
		if (access(cmd_args[0], F_OK | X_OK) >= 0)
			return (ft_strdup(cmd_args[0]));
		return (ms_perror(cmd_args[0], NO_SUCH_FILE_OR_DIR), NULL);
	}
	else if (is_valid_cmd_path(cmd_args[0]) && cmd_args[0][0] != '/')
	{
		index = -1;
		while (program->env_path[++index])
		{
			cmd = ft_strjoin_3(program->env_path[index], "/", cmd_args[0]);
			if (access(cmd, F_OK | X_OK) >= 0)
				return (cmd);
			free(cmd);
		}
	}
	return (ms_cmdnf_error(cmd_args[0]), NULL);
}

int	cmd_handler(void *arg)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_str;
	int		i;

	token = (t_token *)arg;
	cmd_str = dollar_op(token->str);
	if (!cmd_str)
		return (-1);
	cmd = ft_split_custom(cmd_str, " \t");
	free(cmd_str);
	if (!cmd)
		return (-1);
	i = -1;
	while (cmd[++i])
		cmd[i] = replace_quotes(cmd[i]);
	exec_cmd(cmd);
	free_arr(cmd, 1);
	return (-1);
}

static void	not_from_path(char **cmd_args)
{
	t_program	*program;
	int			status;

	program = get_program();
	if (is_assign(cmd_args))
	{
		exec_assign(cmd_args, program->envp);
		return ;
	}
	if (is_builtin(cmd_args[0]))
	{
		program->status = -10;
		status = builtin_execve(cmd_args[0], cmd_args, program->envp);
		if (program->status == -10)
			program->status = status;
		if (program->status == -1)
			program->status = 1;
		return ;
	}
}

void	exec_cmd(char **cmd_args)
{
	t_program	*program;
	pid_t		child;
	char		*cmd;

	program = get_program();
	if (is_assign(cmd_args) || is_builtin(cmd_args[0]))
		return (not_from_path(cmd_args));
	cmd = get_relative_cmd(cmd_args);
	if (!cmd)
		cmd = get_cmd(cmd_args);
	if (!cmd)
		return ;
	child = fork();
	signal(SIGINT, &handler_cmd);
	signal(SIGQUIT, &handler_cmd);
	if (child == CHILD_PROCESS && (!program->is_piped || setup_write_pipe()))
		execve(cmd, cmd_args, program->envp);
	waitpid(child, &program->status, 0);
	program->status %= 255;
	signal(SIGINT, &handler_idle);
	signal(SIGQUIT, SIG_IGN);
	free(cmd);
}
