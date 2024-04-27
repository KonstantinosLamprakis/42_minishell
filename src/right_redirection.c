/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:09 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/27 16:18:50 by lgreau           ###   ########.fr       */
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
}

static char	*get_right_arg(t_token *token)
{
	char	**tmp;
	char	*right_arg;

	tmp = ft_escsplit(token->str + token->start + 1, ft_iswspace, ft_isquote);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	right_arg = ft_strdup(tmp[0]);
	free_arr(tmp, 1);
	if (!right_arg)
		return (NULL);
	return (right_arg);
}

/**
 * @brief Handler wrapper for '>' operator
 *
 * @param arg t_token received from the parser
 */
int	r_redirect_handler(void *arg)
{
	t_token	*token;
	char	*left_arg;
	char	*right_arg;

	token = (t_token *)arg;
	if (!token)
		return (-1);
	left_arg = get_left_arg(token);
	right_arg = get_right_arg(token);
	if (*get_errno() != 0)
		return (-1);
	right_redirection(right_arg, left_arg);
	if (left_arg)
		free(left_arg);
	return (free(right_arg), -1);
}

/**
 * @brief Redirect arg's file descriptor to stdout
 * if nothing is before the redirection or the file in fornt if there's one
 *
 * @param arg openable filename expected
 */
void	right_redirection(char *arg, char *left_arg)
{
	int	right_fd;

	right_fd = ft_open_first(arg, O_WRONLY | O_CREAT, 0644);
	if (right_fd < 0)
		return (set_error((char *)__func__, OPEN));
	if (dup2(right_fd, STDOUT) < 0)
		return (set_error((char *)__func__, DUP));
	if (left_arg)
		ft_parse(left_arg);
	printf("DEBUG\n");
}
