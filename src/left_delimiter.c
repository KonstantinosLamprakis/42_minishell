/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:59:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 09:45:06 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_left_arg(t_token *token)
{
	char	*left_arg;

	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start - 1, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), NULL);
	}
	return (left_arg);
	// tmp = ft_getnth_word(token->str + token->start + 2, 1, ft_iswspace, NULL);
	// if (!tmp)
	// 	return (set_error((char *)__func__, ALLOC));
	// *right_arg = ft_strtrim_if(tmp, ft_iswspace);
	// free(tmp);
	// if (!*right_arg)
	// 	return ;
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
	// char	*tmp;

	token = (t_token *)arg;
	left_arg = get_left_arg(token);
	if (*get_errno() != 0)
		return (-1);

	// if (token->start > 0)
	// {
	// 	left_arg = ft_substr_if(token->str, 0, token->start - 1, ft_iswspace);
	// 	if (!left_arg)
	// 		return (set_error((char *)__func__, ALLOC), -1);
	// }
	// tmp = ft_getnth_word(token->str + token->start + 2, 1, ft_iswspace, NULL);
	// if (!tmp)
	// 	return (set_error((char *)__func__, ALLOC), -1);
	// right_arg = ft_strtrim_if(tmp, ft_iswspace);
	// free(tmp);
	// if (!right_arg)
	// 	return (-1);

	left_delimiter(right_arg, left_arg);
	if (left_arg)
		free(left_arg);
	if (ft_strnstr(token->str, right_arg, ft_strlen(right_arg)) == NULL)
		return (-1);
	offset = (ft_strnstr(token->str, right_arg, ft_strlen(right_arg)) - token->str) + ft_strlen(right_arg);
	return (free(right_arg), offset);
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
	buffer = ft_get_next_line(STDIN);
	while (buffer)
	{
		if (ft_strlen(buffer) == (1 + ft_strlen(program->delimiter))
			&& ft_strncmp(buffer, program->delimiter, ft_strlen(buffer) - 1) == 0)
		{
			free(buffer);
			break ;
		}
		write(here_doc, buffer, ft_strlen(buffer));
		free(buffer);
		write(STDOUT, HERE_DOC_PROMPT, ft_strlen(HERE_DOC_PROMPT));
		buffer = ft_get_next_line(STDIN);
	}
	close(here_doc);
	left_redirection(HERE_DOC_FILE, left_arg);
}
