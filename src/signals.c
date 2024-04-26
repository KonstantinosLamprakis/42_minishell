/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:54 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/26 09:39:15 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handler_on_idle(int signal, siginfo_t *info, void *ucontext);
static void	handler_on_cmd(int signal, siginfo_t *info, void *ucontext);

/**
 * @brief initializes the signals for Ctrl C and Ctrl \
 * Ctrl C = SIGINT -> exit if command is executed, otherwise
 * just print another prommt
 * Ctrl \ = SIGQUIT -> just ignored
 * @return int 0 on success, 1 on error
 */
int	init_signal(void)
{

	signal(SIGQUIT, SIG_IGN);
	put_signal_handler(1);
	return (0);
}

void	put_signal_handler(int is_idle)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if ((sigemptyset(&act.sa_mask) == -1) || \
	(sigaddset(&act.sa_mask, SIGINT) == -1) || \
	(sigaddset(&act.sa_mask, SIGQUIT) == -1))
		return (1);
	if (is_idle)
		act.sa_sigaction = &handler_on_idle;
	else
		act.sa_sigaction = &handler_on_cmd;
	sigaction(SIGINT, &act, NULL);
	return (0);
}

static void	handler_on_cmd(int signal, siginfo_t *info, void *ucontext)
{
	info = NULL;
	ucontext = NULL;
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		get_program()->status = 130;
		exit(130);
	}
}

static void	handler_on_idle(int signal, siginfo_t *info, void *ucontext)
{
	info = NULL;
	ucontext = NULL;
	if (signal == SIGINT)
	{
		rl_replace_line("  ", 0);
		rl_redisplay();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_program()->status = 130;
	}
}
