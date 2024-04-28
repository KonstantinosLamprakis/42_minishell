/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:59:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 09:14:23 by lgreau           ###   ########.fr       */
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

	if (ft_strlen_if(token->str + token->start + 2, ft_iswspace) == 0)
		return (set_error((char *)__func__, SYNTAX), NULL);
	tmp = ft_escsplit(token->str + token->start + 2, ft_iswspace, ft_isquote);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	right_arg = ft_strdup(tmp[0]);
	free_arr(tmp, 1);
	if (!right_arg)
		return (NULL);
	return (right_arg);
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
	int		offset;
	char	*left_arg;
	char	*right_arg;

	token = (t_token *)arg;
	left_arg = get_left_arg(token);
	right_arg = get_right_arg(token);
	if (*get_errno() != 0)
		return (-1);
	left_delimiter(right_arg, left_arg);
	if (left_arg)
		free(left_arg);
	offset = ft_strnstr(token->str, right_arg, ft_strlen(right_arg))
		- token->str + ft_strlen(right_arg);
	offset += ft_isquote(token->str[offset]);
	return (free(right_arg), offset);
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
void	left_delimiter(char *arg, char *left_arg)
{
	t_program	*program;
	char		*buffer;
	int			here_doc;

	program = get_program();
	program->delimiter = arg;
	here_doc = ft_open_first(HERE_DOC_FILE, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (here_doc < 0)
		return ;
	write(STDOUT, HERE_DOC_PROMPT, ft_strlen(HERE_DOC_PROMPT));
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
		write(STDOUT, HERE_DOC_PROMPT, ft_strlen(HERE_DOC_PROMPT));
		buffer = ft_get_next_line(program->std_fd[STDIN]);
	}
	close(here_doc);
	left_redirection(HERE_DOC_FILE, left_arg);
}
