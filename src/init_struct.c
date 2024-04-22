/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:49:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/22 09:52:22 by klamprak         ###   ########.fr       */
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

	tmp = ft_split(program->envp[0], '\n');
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
static void	init_environment(t_program *program)
{
	get_env_paths(program);
}

/**
 * @brief copy everything from old_envp to new_envp
 *
 * @param new_envp pointer to new envp
 * @param old_envp old envp that we will copy to the new one
 */
static void	create_envp(char ***new_envp, char **old_envp)
{
	int		i;
	int		j;
	char	**result;

	if (!old_envp)
		return ;
	i = 0;
	while (old_envp[i])
		i++;
	result = malloc((i + 1) * sizeof(char *));
	if (!result)
		return (set_error((char *)__func__, ALLOC));
	i = -1;
	while (old_envp[++i])
	{
		result[i] = malloc(sizeof(char) * (ft_strlen(old_envp[i]) + 1));
		if (!result[i])
			return (free(result), set_error((char *)__func__, ALLOC));
		j = -1;
		while (old_envp[i][++j] != '\0')
			result[i][j] = old_envp[i][j];
		result[i][j] = '\0';
	}
	result[i] = NULL;
	*new_envp = result;
}

/**
 * @brief Initializes the main program structure
 *
 * @param program
 * @param envp
 */
void	init_struct(t_program *program, char **envp)
{
	create_envp(&(program->envp), envp);
	//init_environment(program);
}
