/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/25 22:01:22 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	bugs:
		- export test="" -> adds multiple "", same export test="test1"
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
		builtin_execve(cmd_ar[0], cmd_ar, program->envp);
		free(line);
		free_arr((void *)cmd_ar, 1);
	}
	set_handler(L_REDIRECT, l_redirect_handler);
	set_handler(OPERATOR_COUNT, cmd_handler);
	char	str[] = "< Makefile cat";
	ft_parse(str);
	clean_struct();
	exit(*get_errno() != 0);
}

