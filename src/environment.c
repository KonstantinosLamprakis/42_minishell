/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:52:26 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/17 11:10:35 by lgreau           ###   ########.fr       */
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
	char	**tmp;
	char	*line;
	int		index;

	tmp = ft_split(program->envp, '\n');
	if (!tmp)
		return (set_error((char *)__func__, ALLOC));
	line = NULL;
	index = -1;
	while (tmp[++index])
	{
		if (ft_strncmp(tmp[index], "PATH=", 5) == 0)
		{
			line = ft_substr(tmp[index], 5, ft_strlen(tmp[index] - 5));
			if (!line)
				return (free_arr((void **)tmp, 1), set_error((char *)__func__,
						ALLOC));
			break ;
		}
	}
	free_arr((void **)tmp, 1);
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
void	init_environment(t_program *program)
{
	get_env_paths(program);
}
