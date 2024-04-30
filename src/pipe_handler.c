/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:17:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 13:24:26 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (ft_strlen_if(token->str + token->start + 1, ft_iswspace) == 0)
		return (ms_syntax_error("newline"), -1);
	left_arg = ft_substr_if(token->str, 0, token->start, ft_iswspace);
	if (*get_errno() != NO_ERROR)
		return (-1);
	if (ft_strlen(left_arg) == 0)
		return (ms_syntax_error("|"), free(left_arg), -1);
	pipe_operation(left_arg);
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
