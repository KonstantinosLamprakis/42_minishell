/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:09 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/25 22:05:55 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	*tmp;
	int		offset;

	token = (t_token *)arg;
	if (!token)
		return (-1);
	printf("\n%s: received token:\n", (char *)__func__);
	printf("  |- string: %s\n", token->str);
	printf("  |- start : %s\n", token->str + token->start);
	left_arg = NULL;
	if (token->start > 0)
	{
		left_arg = ft_substr_if(token->str, 0, token->start - 1, ft_iswspace);
		if (!left_arg)
			return (set_error((char *)__func__, ALLOC), -1);
	}
	printf("  |- left_arg  = %s\n", left_arg);
	tmp = ft_getnth_word(token->str + token->start + 1, 1, ft_iswspace, NULL);
	if (!tmp)
		return (set_error((char *)__func__, ALLOC), -1);
	right_arg = ft_strtrim_if(tmp, ft_iswspace);
	free(tmp);
	if (!right_arg)
		return (-1);
	printf("  |- right_arg = %s\n\n", right_arg);
	left_redirection(right_arg, left_arg);
	if (ft_strnstr(token->str, right_arg, ft_strlen(right_arg)) == NULL)
		return (-1);
	offset = (ft_strnstr(token->str, right_arg, ft_strlen(right_arg)) - token->str) + ft_strlen(right_arg);
	return (offset);
}

/**
 * @brief Redirect arg's file descriptor to stdin
 * if nothing is before the redirection or the file in fornt if there's one
 *
 * @param arg openable filename expected
 * @param left_arg optionnal (= NULL) left part of the redirection
 */
void	left_redirection(char *arg, char *left_arg)
{
	int	left_fd;
	int	right_fd;

	right_fd = ft_open(arg, O_RDONLY, -1);
	if (right_fd < 0)
		return (printf("Tried to open: |%s|\n", arg),
			set_error((char *)__func__, OPEN));
	if (!left_arg)
	{
		printf("Redirecting %d (%s) to %d\n\n", right_fd, arg, STDIN);
		if (dup2(right_fd, STDIN) < 0)
			return (set_error((char *)__func__, DUP));
	}
	else
	{
		left_fd = ft_btoi(left_arg, "0123456789");
		if (*get_errno() != 0)
			return ;
		printf("Redirecting %d to %d\n", right_fd, left_fd);
		printf("TODO: verify that %d is an opened file.\n\n", left_fd);
		// if (dup2(right_fd, left_fd) < 0)
		// 	return (set_error((char *)__func__, DUP));
	}
}
