/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:09 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 15:09:52 by lgreau           ###   ########.fr       */
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
	int		end;
	int		had_quotes;

	if (ft_strlen_if(token->str + token->start + 2, ft_iswspace) == 0)
		return (ms_syntax_error("newline"), NULL);
	had_quotes = (ft_strcount(token->str + token->start + 2, ft_isquote) > 0);
	tmp = ft_escsplit(token->str + token->start + 2, ft_iswspace, ft_isquote);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	end = (ft_strop(tmp[0]) * !had_quotes + had_quotes * ft_strlen(tmp[0]));
	if (end == 0)
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
			- token->str) + ft_strlen(right_arg) + 1;
	tmp = ft_substr(token->str, offset, ft_strlen(token->str + offset));
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	if (left_arg)
		res = ft_strjoin_3(left_arg, " ", tmp);
	else
		res = ft_strdup(tmp);
	free(tmp);
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	return (res);
}

/**
 * @brief Handler wrapper for '>>' operator
 *
 * @param arg t_token received from the parser
 */
int	r_append_handler(void *arg)
{
	t_token	*token;
	char	*left_arg;
	char	*right_arg;
	char	*sub_right;
	int		fd;

	token = (t_token *)arg;
	if (!token)
		return (-1);
	right_arg = get_right_arg(token);
	if (!right_arg)
		return (set_errno(NO_ERROR), token->next);
	fd = right_append(right_arg);
	if (*get_errno() != NO_ERROR)
		return (set_errno(NO_ERROR), token->next);
	left_arg = get_left_arg(token);
	if (*get_errno() != NO_ERROR)
		return (close(fd), set_errno(NO_ERROR), token->next);
	sub_right = extract_used_part(token, left_arg, right_arg);
	free(right_arg);
	if (left_arg)
		free(left_arg);
	if (!sub_right)
		return (close(fd), -1);
	return (ft_parse(sub_right), free(sub_right), close(fd), -1);
}

/**
 * @brief Redirect arg's file descriptor to stdout
 * if nothing is before the redirection or the file in fornt if there's one
 *
 * @param arg openable filename expected
 */
int	right_append(char *arg)
{
	int	right_fd;

	right_fd = ft_open(arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (right_fd < 0)
		return (-1);
	if (dup2(right_fd, STDOUT) < 0)
		return (set_error((char *)__func__, DUP), -1);
	return (right_fd);
}
