/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:54 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/30 18:36:23 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_idle(int sig)
{
	char	*temp;

	if (sig == SIGINT && get_program()->is_on_getline)
	{
		temp = ft_strjoin(rl_line_buffer, "  ");
		rl_replace_line(temp, 0);
		rl_redisplay();
		free(temp);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	get_program()->status = 130;
}

void	handler_cmd(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		get_program()->status = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		get_program()->status = 131;
	}
}

void	handler_exit(int sig)
{
	if (sig == SIGINT)
		get_program()->status = 130;
	exit (get_program()->status);
}
