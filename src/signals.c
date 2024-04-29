/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:54 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/29 10:09:35 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_idle(int sig)
{
	char	*temp;

	if (sig == SIGINT)
	{
		temp = ft_strjoin(rl_line_buffer, "  ");
		rl_replace_line(temp, 0);
		rl_redisplay();
		free(temp);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_program()->status = 130;
	}
}

void	handler_cmd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		get_program()->status = 130;
	}
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		get_program()->status = 131;
	}
}
