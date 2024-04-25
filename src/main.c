/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/25 17:18:44 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	bugs:
		- check for mem leaks
		- fix norminette
		- echo "          f    fg " -> should modify split
	todo: function ft_free to free only if is not NULL
 */

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char *argv[], char *envp[])
{
	// char	str[] = "infile < test/test.txt";
	t_program	*program;
	char		**cmd_ar;
	char		*line;

	atexit(leaks);
	argc = 0;
	argv = NULL;
	init_struct(envp);
	program = get_program();
	while (42)
	{
		line = get_line();
		cmd_ar = ft_split(line, ' ');
		// if(ft_strcmp(cmd_ar[0], "exit") == 0)
		// {
		// 	clean_struct();
		// 	free(line);
		// 	free_arr((void *)cmd_ar, 1);
		// 	break ;
		// }
		builtin_execve(cmd_ar[0], cmd_ar, program->envp);
		free(line);
		free_arr((void *)cmd_ar, 1);
	}
	clean_struct();
	// set_handler(L_REDIRECT, l_redirect_handler);
	// ft_parse(str);
	// exit(*get_errno() != 0);
}

