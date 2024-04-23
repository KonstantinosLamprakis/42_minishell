/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 16:51:13 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	// char	str[] = "infile < test/test.txt";
	t_program	*program;

	argc = 0;
	init_struct(envp);
	program = get_program();
	builtin_execve(argv[1], argv + 1, program->envp);
	// set_handler(L_REDIRECT, l_redirect_handler);
	// ft_parse(str);
	// exit(*get_errno() != 0);
}

