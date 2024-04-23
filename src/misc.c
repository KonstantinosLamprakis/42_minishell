/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:14:56 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 10:21:36 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_opened_fd(void)
{
	t_program	*program;
	int			index;
	int			count;

	program = get_program();
	printf("\nOpenend files table:\t(%d opened files)\n", program->opened_count);
	index = -1;
	count = program->opened_count;
	while (++index >= 0 && count > 0)
	{
		if (index == 0 || program->opened_files[index] != 0)
		{
			printf("  |- %d: %d\n", index, program->opened_files[index]);
			count--;
		}
		else
			printf("  |- %d: has been closed.\n", index);
	}
	print_std_fd();
}

void	print_std_fd(void)
{
	t_program	*program;

	program = get_program();
	printf("\nStandard file descriptors:\n");
	printf("  |- STDIN  saved as %d\n", program->std_fd[STDIN]);
	printf("  |- STDOUT saved as %d\n", program->std_fd[STDOUT]);
	printf("  |- STDERR saved as %d\n", program->std_fd[STDERR]);
}
