/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 09:43:27 by klamprak         ###   ########.fr       */
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
	// char	str[] = "infile < test/test.txt";
	t_program	*program;
	// char		**cmd_ar;
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
		// printf("%s\n", line);
		// cmd_ar = ft_escsplit(line, ft_iswspace, ft_isquote);
		// printf("%s\n", cmd_ar[1]);
		// builtin_execve(cmd_ar[0], cmd_ar, program->envp);
		free(line);
		reset_struct();
		// free_arr(cmd_ar, 1);
	}
	clean_struct();
	exit(*get_errno() != 0);
}

