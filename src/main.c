/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 13:36:40 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	tester2: https://github.com/LucasKuhn/minishell_tester
	bugs:
			- /bin/echo $HALLO42$HOME$sda$USER: need to check what command we pass, because it works ex. for $HOME
		- louen
			- heredoc with single char delimiter
			- env -i ./minishell -> cat -> segfault
			- 35 echo "exit_code ->$? user ->$USER home -> $HOME"
		- Louen notes:
			if inside stdin waiting for input : CTRL + D or CTRL + C doesn't work, intended ?
			After using CTRL + C to kill an ongoing command, nothing works anymore (maybe just need a reset ?)
			it's still possible to CTRL + C again to have a new prompt, but you can't execute cmds or CTRL + D to quit
			For here_doc (<<) + CTRL D handling
			Monday:
				- when trying to find absolute path cmd: no such file or dir (NOT cmd not found)
				- error messages should include the issue
					(/bin/echo 1 | kaka
					=> bash: kaka: command not found)
				(Don't know if it's a problem)
				CTRL + D while in here_doc (<<)
					- prints D, but it doesn't in bash ?
					- also creates a sub shell
	todo:
		- tested on empty environment
		- clean_struct should clean everything because we use it at signals and at exit
		- delete and clean git branches
		- check mem leaks
		- TODO OPTIONAL
			- error at dollar operator ${name -> bad substitution
			- CDPATH at cd builtin
			- ctrl D should decrease SHLVL if its > 1 and clean everything

*/

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;

	// atexit(leaks);
	argc++;
	argv++;
	init_struct(envp);
	signal(SIGINT, &handler_idle);
	signal(SIGQUIT, SIG_IGN);
	line = get_line();
	while (line)
	{
		if (validate_line(line))
			ft_parse(line);
		free(line);
		reset_struct();
		line = get_line();
	}
	clean_struct();
	exit(get_program()->status);
}
