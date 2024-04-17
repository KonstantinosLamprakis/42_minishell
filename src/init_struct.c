/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:49:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/17 18:05:29 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Extracts the paths from the program environment
 *
 * @param program
 */
static void	get_env_paths(t_program *program)
{
	char	*line;
	int		index;

	line = NULL;
	index = -1;
	while (program->envp[++index])
	{
		if (ft_strncmp(program->envp[index], "PATH=", 5) == 0)
		{
			line = ft_substr(program->envp[index], 5,
					ft_strlen(program->envp[index] - 5));
			if (!line)
				return (set_error((char *)__func__, ALLOC));
			break ;
		}
	}
	program->env_path = ft_split(line, ':');
	if (!program->env_path)
		return (free(line), set_error((char *)__func__, ALLOC));
	free(line);
}

/**
 * @brief Initialize the environment for the program
 * @todo add the path to the hand-made builting functions & the local variables
 *
 * @param program
 */
static void	init_environment(t_program *program)
{
	get_env_paths(program);
}

/**
 * @brief Initializes the main program structure
 *
 * @param program
 * @param envp
 */
void	init_struct(t_program *program, char **envp)
{
	program->envp = envp;
	init_environment(program);
	if (*get_errno() != 0)
		return ;
	program->opened_count = 0;
}
