/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 13:57:13 by lgreau           ###   ########.fr       */
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
		- exit error after merging, the pointer that freed is not allocated
		- Ctrl C should only erase ^C, not other prommt
		- Ctrl \, when you run a command should send SIG_QUIT ex. cat,
		then ctrl \, exits the cat command
		- check the output of put_signal_handler for errors
	todo:
		- function ft_free to free only if is not NULL
		- add return (set_error((char *)__func__, INVALID_ARG)); at get_env_value errors
		- clean_struct should clean everythink because we use it at signals and at exit
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
	if (init_signal() == 1)
		exit (1);
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

