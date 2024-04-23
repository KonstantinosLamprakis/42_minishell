/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:02:48 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 17:12:06 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	close_files(t_program *program)
{
	int	index;

	index = -1;
	while (program->opened_count >= 0 && ++index >= 0)
		if (program->opened_files[index] >= 0 && program->opened_count--)
			if (close(program->opened_files[index]) < 0)
				return (set_error((char *)__func__, CLOSE));
}

/**
 * @brief Cleans up the program structure namely:
 * 	- close every files still opened
 *
 * @param program
 */
void	clean_struct(void)
{
	t_program	*program;

	program = get_program();
	close_files(program);
}
