/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:17:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/25 10:46:44 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_pipe_cmd(char **left_cmd_args)
{
	t_program	*program;
	char		*cmd;
	pid_t		child;

	cmd = get_cmd(left_cmd_args);
	if (!cmd)
		return ;
	program = get_program();
	child = fork();
	if (child < 0)
		return (set_error((char *)__func__, FORK));
	if (child == CHILD_PROCESS)
	{
		printf("Redirecting pipe_write_end to %d\n", STDOUT);
		if (dup2(program->pipe_end[PIPE_WRITE], STDOUT) < 0)
			return (set_error((char *)__func__, DUP));
		close(program->pipe_end[PIPE_READ]);
		execve(cmd, left_cmd_args, program->envp);
	}
	waitpid(child, &program->status, 0);
}

int	pipe_handler(void *arg)
{
	t_token	*token;
	char	*left_arg;

	token = (t_token *)arg;

	printf("\n%s: received token:\n", (char *)__func__);
	printf("  |- string: %s\n", token->str);
	printf("  |- start : %s\n", token->str + token->start);

	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start - 1, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), -1);
	}
	printf("  |- left_arg  = %s\n", left_arg);

	printf("\n");

	pipe_operation(left_arg);

	return (token->start + 1);
}

void	pipe_operation(char *left_arg)
{
	t_program	*program;
	char		**cmd_args;

	cmd_args = ft_escsplit(left_arg, ft_iswspace, ft_isquote);
	if (!cmd_args)
		return ;
	program = get_program();
	pipe(program->pipe_end);
	exec_pipe_cmd(cmd_args);
	close(program->pipe_end[PIPE_WRITE]);
	printf("Redirecting pipe_read_end to %d\n", STDIN);
	if (dup2(program->pipe_end[PIPE_READ], STDIN) < 0)
		return (set_error((char *)__func__, DUP));
}
