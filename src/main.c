/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 15:02:21 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	tester2: https://github.com/LucasKuhn/minishell_tester
	bugs:
		- dollar sign for '' and "" different behavior
		- Louen notes:
			if inside stdin waiting for input : CTRL + D or CTRL + C doesn't work, intended ?
			After using CTRL + C to kill an ongoing command, nothing works anymore (maybe just need a reset ?)
			it's still possible to CTRL + C again to have a new prompt, but you can't execute cmds or CTRL + D to quit
			For here_doc (<<) + CTRL D handling
			Monday:
				- /bin/echo $HOME$USER returns "", maybe not handling no spacing ?
				- Bash: a="asd" => in env: a=asd, quotes trimmed
				- With already existing a: (couldn't replicate)
					minishell > export a="asd"
					export: �B: not valid identifier
					zsh: segmentation fault  ./minishell
				- when trying to find absolute path cmd: no such file or dir (NOT cmd not found)
				- error messages should include the issue
					(/bin/echo 1 | kaka
					=> bash: kaka: command not found)
				(Don't know if it's a problem)
				CTRL + D while in here_doc (<<)
					- prints D, but it doesn't in bash ?
					- also creates a sub shell
	todo:
		- clean_struct should clean everything because we use it at signals and at exit
		- delete and clean git branches
		- check mem leaks
		- replace fprintf because is forbitten
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
		ft_parse(line);
		free(line);
		reset_struct();
		get_program()->status = 0;
		line = get_line();
	}
	clean_struct();
	exit(*get_errno() != 0);
}

