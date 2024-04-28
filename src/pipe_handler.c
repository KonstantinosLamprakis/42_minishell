/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:17:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 12:47:06 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	exec_pipe_cmd(char **left_cmd_args)
// {
// 	t_program	*program;
// 	char		*cmd;
// 	pid_t		child;

// 	cmd = get_cmd(left_cmd_args);
// 	if (!cmd)
// 		return ;
// 	program = get_program();
// 	child = fork();
// 	if (child < 0)
// 		return (set_error((char *)__func__, FORK));
// 	if (child == CHILD_PROCESS)
// 	{
// 		if (dup2(program->pipe_end[PIPE_WRITE], STDOUT) < 0)
// 			return (set_error((char *)__func__, DUP));
// 		close(program->pipe_end[PIPE_READ]);
// 		execve(cmd, left_cmd_args, program->envp);
// 	}
// 	free(cmd);
// 	waitpid(child, &program->status, 0);
// }

static void	ft_pipe(void)
{
	t_program	*program;

	program = get_program();
	pipe(program->pipe_end);
	program->pipe_save_read[program->depth] = program->pipe_end[PIPE_READ];
	program->pipe_save_write[program->depth] = program->pipe_end[PIPE_WRITE];
}

int	pipe_handler(void *arg)
{
	t_token	*token;
	char	*left_arg;

	token = (t_token *)arg;
	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), -1);
	}
	pipe_operation(left_arg);
	if (left_arg)
		free(left_arg);
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
	ft_pipe();
	program->is_piped = 1;
	ft_parse(left_arg);
	program->is_piped = 0;
	free_arr(cmd_args, 1);
	close(program->pipe_save_write[program->depth]);
	if (dup2(program->pipe_save_read[program->depth], STDIN) < 0)
		return (set_error((char *)__func__, DUP));
}
