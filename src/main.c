/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/27 19:23:47 by klamprak         ###   ########.fr       */
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
		- export test_3421 -> not valid identifirer
		- export test1="" => not valid identifier -> split gives a NULL arg extra
			- I fixed that in my code(b_export()), but I thing is parser error
		- parser error when provides a wrong command, then you can not continue
		- "echo test"
		- seg fault when command not found
		- ctrl D should decrease SHLVL if its > 1 and clean everything
		- check the output of put_signal_handler for errors
	todo:
		- clean_struct should clean everything because we use it at signals and at exit
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
	signal(SIGQUIT, SIG_IGN);
	program = get_program();
	while (42)
	{
		if (isatty(fileno(stdin)))
			line = get_line();
		else
			line = ft_get_next_line_nonl(fileno(stdin));
		// line = get_line();
		// if (!line)
		// 	continue ;
		ft_parse(line);
		free(line);
		reset_struct();
	}
	clean_struct();
	exit(*get_errno() != 0);
}

