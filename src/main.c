/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/28 20:58:39 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	bugs:
		- export test1="" => not valid identifier -> split gives a NULL arg extra
			- I fixed that in my code(b_export()), but I thing is parser error
		- "echo test" -> wrong error number instead of command not found
		- test2=" df" -> invalid arg-> wrong
		- export test2=" this is" -> not valid identifier -> wrong
		- ERROR with split ex. export test="value"
			- returns test="value" and value. Should return only the first
			- should split "" only when they are between spaces
		- ctrl D should decrease SHLVL if its > 1 and clean everything
	todo:
		- clean_struct should clean everything because we use it at signals and at exit
		- delete and clean git branches
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
		ft_parse(line);
		free(line);
		reset_struct();
	}
	clean_struct();
	exit(*get_errno() != 0);
}

