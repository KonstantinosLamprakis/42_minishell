/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 22:08:20 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	tester2: https://github.com/LucasKuhn/minishell_tester
	bugs:
		- unset ? : invalid identifier
		- export test1="" => not valid identifier -> split gives a NULL arg extra
			- I fixed that in my code(b_export()), but I thing is parser error
		- "echo test" -> wrong error number instead of command not found
		- test2=" df" -> invalid arg-> wrong
		- export test2=" this is" -> not valid identifier -> wrong
		- ERROR with split ex. export test="value"
			- returns test="value" and value. Should return only the first
			- should split "" only when they are between spaces

		- ctrl D should decrease SHLVL if its > 1 and clean everything
		- echo << test << test2 << and then signals (fix it by fork after get_line
		and just kill child)
		- emtpy command gives invalid argument error
		- Luen notes:
			(Worked fine but broke it by addind () + | handling)
			cmd | cmd2 << limiter :
				- rn: reads from the pipe until limiter
				- should: read from
			(Sometimes (couldn't repliacte))
			cat<Makefile:
				- rn: equivalent to cat Makefile or < Makefile cat. BUT keeps stdin open and waiting for input
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
				- builtins not going into the pipes
				- when trying to find absolute path cmd: no such file or dir (NOT cmd not found)
				- error messages should include the issue
					(/bin/echo 1 | kaka
					=> bash: kaka: command not found)
				- ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > out | cat << 'stop3'
				minishell(57114,0x114a04dc0) malloc: *** error for object 0x3000000000000000: pointer being freed was not allocated
				minishell(57114,0x114a04dc0) malloc: *** set a breakpoint in malloc_error_break to debug
				- cat<<asd>out
					=> current limiter is first "word" by wspace.
					BUT it should stop if operator
				(Don't know if it's a problem)
				CTRL + D while in here_doc (<<)
					- prints D, but it doesn't in bash ?
	todo:
		- clean_struct should clean everything because we use it at signals and at exit
		- delete and clean git branches
		- check mem leaks
		- replace fprintf because is forbitten
		- echo << test <<
		- TODO OPTIONAL
			- error at dollar operator ${name -> bad substitution
			- CDPATH at cd builtin
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
	while (42)
	{
		if (isatty(fileno(stdin)))
			line = get_line();
		else
			line = ft_get_next_line_nonl(fileno(stdin));
		ft_parse(line);
		free(line);
		reset_struct();
		get_program()->status = 0;
	}
	clean_struct();
	exit(*get_errno() != 0);
}

