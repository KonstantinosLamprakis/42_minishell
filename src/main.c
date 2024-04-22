/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/22 17:28:31 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_program	program;
	char		*line_read;

	if (argc && argv)
		line_read = NULL;
	init_struct(&program, envp);
	while (42)
	{
		line_read = get_line();
		if (!line_read)
			continue ;
		// execute the command
		free(line_read); // probably should go at free function
	}
	exit(*get_errno() != 0);
}

