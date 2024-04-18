/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:09 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/18 12:39:27 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Handler wrapper for '<' operator
 *
 * @param arg t_token received from the parser
 */
void	l_redirect_handler(void *arg)
{
	t_token	*token;
	char	*left_arg;
	char	*right_arg;
	int		*lengths;

	token = (t_token *)arg;
	if (!token)
		return ;
	lengths = get_lengths();
	printf("%s: received token:\n", (char *)__func__);
	left_arg = ft_substr(token->str, 0, token->start - 1);
	if (!left_arg)
		return (set_error((char *)__func__, ALLOC));
	printf("  |- left_arg  = %s\n", left_arg);
	right_arg = ft_substr(token->str, token->start + lengths[token->op], token->next_operator - token->start - lengths[token->op]);
	if (!right_arg)
		return (set_error((char *)__func__, ALLOC));
	printf("  |- right_arg = %s\n", right_arg);
}

/**
 * @brief Redirect arg's file descriptor to stdin
 * if nothing is before the redirection or the file in fornt if there's one
 *
 * @param program structure with all the informations
 * @param arg openable filename expected
 * @param left_arg optionnal (= NULL) left part of the redirection
 */
void	left_redirection(t_program *program, char *arg, char *left_arg)
{
	int	left_fd;
	int	right_fd;

	right_fd = ft_open(program , arg, O_RDONLY, -1);
	if (right_fd < 0)
		return (set_error((char *)__func__, OPEN));
	if (!left_arg)
	{
		printf("Redirecting %d to %d\n", right_fd, STDIN);
		if (dup2(right_fd, STDIN) < 0)
			return (set_error((char *)__func__, DUP));
	}
	else
	{
		left_fd = ft_btoi(left_arg, "0123456789");
		if (*get_errno() != 0)
			return ;
		printf("Redirecting %d to %d\n", right_fd, left_fd);
		if (dup2(right_fd, left_fd) < 0)
			return (set_error((char *)__func__, DUP));
	}
}
