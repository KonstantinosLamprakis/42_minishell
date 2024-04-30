/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:23:33 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 13:37:07 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Overriding open to save the file descriptor in program
 * for easy cleanup
 *
 * @param file_name to open
 * @param flags to open the file with
 * @param mode optionnal (= -1) mode to open the file with
 * @return int
 */
int	ft_open(char *file_name, int flags, int mode)
{
	t_program	*program;
	int			fd;

	program = get_program();
	if (mode < 0)
		fd = open(file_name, flags);
	else
		fd = open(file_name, flags, mode);
	if (fd < 0)
		return (ms_perror(file_name, OPEN), -1);
	program->opened_files[program->opened_count++] = fd;
	return (fd);
}

/**
 * @brief Opens and save to the first empty slot in programs opened_files list
 * *
 * @param file_name
 * @param flags
 * @param mode optionnal (= -1) mode to open the file with
 * @return int
 */
int	ft_open_first(char *file_name, int flags, int mode)
{
	t_program	*program;
	int			index;
	int			fd;

	program = get_program();
	index = 1;
	while (index < program->opened_count && program->opened_files[index] > 0)
		index++;
	if (mode < 0)
		fd = open(file_name, flags);
	else
		fd = open(file_name, flags, mode);
	if (fd < 0)
		return (ms_perror(file_name, OPEN), -1);
	program->opened_files[index] = fd;
	program->opened_count++;
	return (fd);
}
