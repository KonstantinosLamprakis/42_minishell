/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 11:48:16 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	tester: https://github.com/zstenger93/42_minishell_tester
	bugs:
		- export test="" -> adds multiple "", same export test="test1"
		- echo " test -> seg fault
		- ctrl D should decrease SHLVL if its > 1 and clean everything
	todo: function ft_free to free only if is not NULL
 */


// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_program	*program;
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
		free(line);
		reset_struct();
	}
	clean_struct();
	exit(*get_errno() != 0);
}

