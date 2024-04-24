/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 07:36:27 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

