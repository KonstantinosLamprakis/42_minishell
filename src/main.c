/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 19:02:32 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	bugs:
		- export name+=value(to existing and new ones vars)
		- SHLVL: equal to +1 if valid or 1 if invalid(ex negative or string)
		- CDPATH
		- commands with uppercase
		- error msgs to be the same
		- check for mem leaks
		- fix norminette
		- ~ should give home dir even if HOME unseted
		- OLDPWD doesn't exists initally
		- error when pwd takes args
 */

int	main(int argc, char *argv[], char *envp[])
{
	// char	str[] = "infile < test/test.txt";
	t_program	*program;
	char		**cmd_ar;

	argc = 0;
	argv = NULL;
	init_struct(envp);
	program = get_program();
	while (42)
	{
		cmd_ar = ft_split(get_line(), ' ');
		builtin_execve(cmd_ar[0], cmd_ar, program->envp);
	}
	// set_handler(L_REDIRECT, l_redirect_handler);
	// ft_parse(str);
	// exit(*get_errno() != 0);
}

