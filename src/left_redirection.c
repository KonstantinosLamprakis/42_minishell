/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:09 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 08:34:49 by lgreau           ###   ########.fr       */
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

	if (ft_strlen_if(token->str + token->start + 1, ft_iswspace) == 0)
		return (set_error((char *)__func__, SYNTAX), NULL);
	tmp = ft_escsplit(token->str + token->start + 1, ft_iswspace, ft_isquote);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), NULL);
	right_arg = ft_strdup(tmp[0]);
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
 * @brief Handler wrapper for '<' operator
 *
 * @param arg t_token received from the parser
 */
int	l_redirect_handler(void *arg)
{
	t_token	*token;
	char	*left_arg;
	char	*right_arg;
	char	*sub_right;

	token = (t_token *)arg;
	if (!token)
		return (-1);
	left_arg = get_left_arg(token);
	right_arg = get_right_arg(token);
	if (*get_errno() != 0)
		return (-1);
	sub_right = extract_used_part(token, left_arg, right_arg);
	if (!sub_right)
		return (-1);
	left_redirection(right_arg, sub_right);
	if (left_arg)
		free(left_arg);
	return (free(right_arg), -1);
}

/**
 * @brief Redirect arg's file descriptor to stdin
 * if nothing is before the redirection or the file in fornt if there's one
 *
 * @param arg openable filename expected
 * @param left_arg optionnal (= NULL) left part of the redirection
 */
void	left_redirection(char *arg, char *sub_right)
{
	int	right_fd;

	right_fd = ft_open(arg, O_RDONLY, -1);
	if (right_fd < 0)
		return (set_error((char *)__func__, OPEN));
	if (dup2(right_fd, STDIN) < 0)
		return (set_error((char *)__func__, DUP));
	if (sub_right)
		ft_parse(sub_right);
}
