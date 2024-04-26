/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 17:49:05 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	bugs:
		- export test="" -> adds multiple "", same export test="test1"
			- maybe split's return value should also include "", and not remove
			them
		- echo " test -> seg fault
		- ctrl D should decrease SHLVL if its > 1 and clean everything
		- Ctrl \, when you run a command should send SIG_QUIT ex. cat,
		then ctrl \, exits the cat command
		- check the output of put_signal_handler for errors
	todo:
		- clean_struct should clean everythink because we use it at signals and at exit
		- delete and clean git branches
		- replace maybe ~, $() etc. before parsing
		- handling assigment operator
 */


// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_program	*program;
	char		*line;

	// atexit(leaks);
	argc = 0;
	argv = NULL;
	init_struct(envp);
	signal(SIGINT, &handler_idle);
	signal(SIGQUIT, &handler_idle);
	program = get_program();
	while (42)
	{
		line = get_line();
		if (!line)
			continue ;
		ft_parse(line);
		free(line);
		reset_struct();
	}
	clean_struct();
	exit(*get_errno() != 0);
}

