/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:59:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 17:32:05 by lgreau           ###   ########.fr       */
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
	if (!had_quotes && end == 0)
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

	offset = ft_strlen(token->str);
	if (ft_strlen(right_arg) > 0)
		offset = (ft_strnstr(token->str + token->start + 2, right_arg,
					ft_strlen(right_arg)) - token->str) + ft_strlen(right_arg)
			+ (ft_strcount(token->str + token->start + 2, ft_isquote) > 0);
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

static int	setup_args(t_token *token, char *right_arg)
{
	char	*left_arg;
	char	*sub_right;
	int		here_doc;

	here_doc = left_redirection(HERE_DOC_FILE);
	if (*get_errno() != NO_ERROR)
		return (set_errno(NO_ERROR), token->next);
	left_arg = get_left_arg(token);
	if (*get_errno() != NO_ERROR)
		return (close(here_doc), set_errno(NO_ERROR), token->next);
	sub_right = extract_used_part(token, left_arg, right_arg);
	free(right_arg);
	if (!sub_right)
		return (-1);
	if (left_arg)
		free(left_arg);
	ft_parse(sub_right);
	free(sub_right);
	close(here_doc);
	return (-1);
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
	char	*right_arg;
	pid_t	parent;

	token = (t_token *)arg;
	right_arg = get_right_arg(token);
	if (!right_arg)
		return (set_errno(NO_ERROR), token->next);
	parent = fork();
	if (parent < 0)
		return (set_error((char *)__func__, FORK), -1);
	else if (parent != CHILD_PROCESS)
	{
		waitpid(parent, NULL, 0);
		return (setup_args(token, right_arg));
	}
	signal(SIGINT, &handler_exit);
	signal(SIGQUIT, &handler_exit);
	left_delimiter(right_arg);
	exit(0);
}
