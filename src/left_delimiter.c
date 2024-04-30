/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:59:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 14:10:45 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_left_arg(t_token *token)
{
	char	*left_arg;

	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), NULL);
	}
	return (left_arg);
}

static char	*get_right_arg(t_token *token)
{
	char	**tmp;
	char	*right_arg;
	int		end;
	int		had_quotes;

	if (ft_strlen_if(token->str + token->start + 2, ft_iswspace) == 0)
		return (ms_syntax_error("newline"), NULL);
	had_quotes = (ft_strcount(token->str + token->start + 2, ft_isquote) > 0);
	tmp = ft_escsplit(token->str + token->start + 2, ft_iswspace, ft_isquote);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	end = (ft_strop(tmp[0]) * !had_quotes + had_quotes * ft_strlen(tmp[0]));
	if (end <= 0)
		return (ms_syntax_error(ft_ltruncate(tmp[0], 1)), free_arr(tmp, 1),
			NULL);
	right_arg = ft_substr(tmp[0], 0, end);
	free_arr(tmp, 1);
	if (!right_arg)
		return (NULL);
	return (right_arg);
}

static char	*extract_used_part(t_token *token, char *left_arg, char *right_arg)
{
	char	*res;
	char	*tmp;
	int		offset;

	offset = (ft_strnstr(token->str, right_arg, ft_strlen(right_arg))
			- token->str) + ft_strlen(right_arg) + (ft_strcount(token->str
				+ token->start + 2, ft_isquote) > 0);
	tmp = ft_substr(token->str, offset, ft_strlen(token->str + offset));
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	if (left_arg)
		res = ft_strjoin(left_arg, tmp);
	else
		res = ft_strdup(tmp);
	free(tmp);
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	return (res);
}

/**
 * @brief "<<" operator handler, expects a string as right argument
 *
 * @param arg
 * @return int
 */
int	l_delimiter_handler(void *arg)
{
	t_token	*token;
	char	*left_arg;
	char	*right_arg;
	char	*sub_right;
	pid_t	p;
	int		status;

	token = (t_token *)arg;
	left_arg = get_left_arg(token);
	right_arg = get_right_arg(token);
	if (*get_errno() != 0)
		return (-1);
	sub_right = extract_used_part(token, left_arg, right_arg);
	if (!sub_right)
		return (-1);
	p = fork();
	if (p < 0)
		return (set_error((char *)__func__, FORK), -1);
	else if (p != 0)
		return(waitpid(p, &status, 0), status);
	signal(SIGINT, &handler_exit);
	signal(SIGQUIT, &handler_exit);
	left_delimiter(right_arg);
	left_redirection(HERE_DOC_FILE, sub_right);
	if (left_arg)
		free(left_arg);
	return (free(right_arg), free(sub_right), -1);
}

static int	is_delimiter(char *buffer)
{
	t_program	*program;

	if (!buffer)
		return (set_error((char *)__func__, INVALID_ARG), -1);
	program = get_program();
	return (ft_strlen(buffer) == (1 + ft_strlen(program->delimiter))
		&& ft_strncmp(buffer, program->delimiter, ft_strlen(buffer) - 1) == 0);
}

/**
 * @brief Reads from stdin until DELIMITER
 * then redirects the read content to stdin
 *
 * @param arg Delimiter to read from stdin until
 * @param left_arg optionnal (= NULL) argument defining to which fd
 * the redirection occurs
 */
void	left_delimiter(char *arg)
{
	t_program	*program;
	char		*buffer;
	int			here_doc;

	program = get_program();
	program->delimiter = arg;
	here_doc = ft_open_first(HERE_DOC_FILE, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (here_doc < 0)
		return ;
	write(program->std_fd[STDOUT], HERE_DOC_PROMPT, ft_strlen(HERE_DOC_PROMPT));
	buffer = ft_get_next_line(program->std_fd[STDIN]);
	while (buffer)
	{
		if (is_delimiter(buffer))
		{
			free(buffer);
			break ;
		}
		write(here_doc, buffer, ft_strlen(buffer));
		free(buffer);
		write(program->std_fd[STDOUT], HERE_DOC_PROMPT,
				ft_strlen(HERE_DOC_PROMPT));
		buffer = ft_get_next_line(program->std_fd[STDIN]);
	}
	close(here_doc);
}
