/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:49:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 12:08:25 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

static void	update_shlvl(void);

t_program	*get_program(void)
{
	static t_program	program;

	return (&program);
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
 * @brief Initialize the environment for the program
 * @todo add the path to the hand-made builting functions & the local variables
 *
 * @param program
 */
static void	init_environment(t_program *program)
{
	get_env_paths(program);
	save_std_fd(program);
	set_handler(AND, and_handler);
	set_handler(OR, or_handler);
	set_handler(PIPE, pipe_handler);
	set_handler(L_REDIRECT, l_redirect_handler);
	set_handler(L_DELIMITER, l_delimiter_handler);
	set_handler(OPERATOR_COUNT, cmd_handler);
}

/**
 * @brief Initializes the main program structure
 *
 * @param envp
 */
void	init_struct(char **envp)
{
	t_program	*program;
	char		*temp;
	char		*home;

	program = get_program();
	create_envp(&(program->envp), envp);
	del_from_envp(program->envp, "OLDPWD");
	program->opened_count = 0;
	program->exp_v = malloc(1 * sizeof(char *));
	if (!program->exp_v)
		return (set_error((char *)__func__, ALLOC));
	program->exp_v[0] = NULL;
	program->loc_v = malloc(1 * sizeof(char *));
	if (!program->loc_v)
		return (set_error((char *)__func__, ALLOC));
	program->loc_v[0] = NULL;
	home = get_env_value(program->envp, "HOME", NULL);
	if (home)
	{
		temp = ft_strjoin("~=", home);
		add_to_envp(&program->loc_v, temp, -1);
		free(home);
		free(temp);
	}
	program->status = 0;
	update_shlvl();
	init_environment(program);
	if (*get_errno() != 0)
		return ;
}

static void	update_shlvl(void)
{
	char	*value;
	int		i;
	int		shlvl;

	value = get_env_value(get_program()->envp, "SHLVL", NULL);
	if (!value)
	{
		replace_envp_key(&get_program()->envp, "SHLVL", "1");
		return ;
	}
	i = 0;
	while (value[i] >= '0' && value[i] <= '9')
		i++;
	if (value[i] != '\0' || i > 10)
		shlvl = 0;
	else
		shlvl = ft_atoi(value);
	shlvl++;
	free(value);
	value = ft_itoa(shlvl);
	replace_envp_key(&get_program()->envp, "SHLVL", value);
	free(value);
}
