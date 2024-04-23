/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:49:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 15:08:34 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_program	*get_program(void)
{
	static t_program	program;

	return (&program);
}

/**
 * @brief Extracts the paths from the program environment
 *
 * @param program
 */
static void	get_env_paths(t_program *program)
{
	char	*line;

	line = get_env_value(program->envp, "PATH", NULL);
	if (!line)
		return (set_error((char *)__func__, INVALID_ARG));
	program->env_path = ft_split(line, ':');
	free(line);
	if (!program->env_path)
		return (set_error((char *)__func__, ALLOC));
}

/**
 * @brief Saves the std file descriptor (STDIN, OUT & ERR) in the program
 * for future "reset" and to allow file descriptor maipulation w/o losing them
 *
 * @param program
 */
static void	save_std_fd(t_program *program)
{
	int	std;

	std = -1;
	while (++std < 3)
	{
		program->std_fd[std] = dup(std);
		if (program->std_fd[std] < 0)
			return (set_error((char *)__func__, DUP));
		program->opened_files[program->opened_count++] = std;
	}
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
	save_std_fd(program);
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
 * @param envp
 */
void	init_struct(char **envp)
{
	t_program *program;

	program = get_program();
	program->opened_count = 0;
	create_envp(&(program->envp), envp);
	init_environment(program);
	if (*get_errno() != 0)
		return ;
}
