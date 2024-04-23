/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 16:17:06 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	argc = 0;
	argv = NULL;
	init_struct(envp);
	set_handler(L_REDIRECT, l_redirect_handler);

	init_struct(&program, envp);
	builtin_execve(argv[1], argv + 1, program.envp);
	// builtin_execve("env", argv + 1, program.envp);
	char	str[] = "infile < test/test.txt";

	ft_parse(str);

	exit(*get_errno() != 0);
}

