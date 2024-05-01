/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_delimiter2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:24:59 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 17:32:23 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_delimiter(char *buffer)
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
	char		*buffer;
	char		*tmp;
	int			here_doc;

	get_program()->delimiter = arg;
	here_doc = ft_open_first(HERE_DOC_FILE, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (here_doc < 0)
		return ;
	write(get_program()->std_fd[STDOUT], HERE_DOC_PROMPT,
		ft_strlen(HERE_DOC_PROMPT));
	buffer = ft_get_next_line(get_program()->std_fd[STDIN]);
	while (buffer && !is_delimiter(buffer))
	{
		tmp = dollar_op(buffer);
		write(here_doc, tmp, ft_strlen(tmp));
		free(tmp);
		write(get_program()->std_fd[STDOUT], HERE_DOC_PROMPT,
			ft_strlen(HERE_DOC_PROMPT));
		buffer = ft_get_next_line(get_program()->std_fd[STDIN]);
	}
	if (buffer)
		free(buffer);
	close(here_doc);
}
