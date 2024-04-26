/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:54 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/26 13:08:12 by klamprak         ###   ########.fr       */
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
	int	i;

	i = put_signal_handler(1, SIGQUIT);
	i = i || put_signal_handler(1, SIGINT);
	return (i);
}

/**
 * @brief switch the signal handler for a signal
 * according to the fact if is idle, or if it is the command execution
 *
 * @param is_idle 1 if its idle(parrent process), 0 if its on command(child)
 * @param signal : SIGIN and SIGQUIT
 * @return int 1 on error, 0 on success
 */
int	put_signal_handler(int is_idle, int sig)
{
	struct sigaction	act;

	if (sig == SIGQUIT && is_idle)
	{
		signal(SIGQUIT, SIG_IGN);
		return (0);
	}
	ft_memset(&act, 0, sizeof(act));
	if ((sigemptyset(&act.sa_mask) == -1) || \
	(sigaddset(&act.sa_mask, SIGINT) == -1) || \
	(sigaddset(&act.sa_mask, SIGQUIT) == -1))
		return (1);
	if (is_idle)
		act.sa_sigaction = &handler_on_idle;
	else
		act.sa_sigaction = &handler_on_cmd;
	sigaction(sig, &act, NULL);
	return (0);
}

static void	handler_on_cmd(int signal, siginfo_t *info, void *ucontext)
{
	info = NULL;
	ucontext = NULL;
	if (signal == SIGINT)
	{
		printf("\n");
		get_program()->status = 130;
		exit(130);
	}
	// if (signal == SIGQUIT)
	// {
	// 	printf("Quit: 3\n");
	// 	get_program()->status = 131;
	// 	exit(131);
	// }
}

static void	handler_on_idle(int signal, siginfo_t *info, void *ucontext)
{
	int		len;
	char	*temp;

	info = NULL;
	ucontext = NULL;
	if (signal == SIGINT)
	{
		len = ft_strlen(rl_line_buffer);
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
