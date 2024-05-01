/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:49:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 17:23:12 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_lists(void);

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
	char	cwd[PATH_MAX];

	line = get_env_value(program->envp, "PATH", NULL);
	if (!line)
	{
		replace_envp_key(&get_program()->envp, "PATH", getcwd(cwd, sizeof(cwd)));
		line = get_env_value(program->envp, "PATH", NULL);
		ms_perror_custom("PATH", "", ENV_NOT_SET);
	}
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
	set_handler(R_REDIRECT, r_redirect_handler);
	set_handler(L_DELIMITER, l_delimiter_handler);
	set_handler(R_APPEND, r_append_handler);
	set_handler(OPERATOR_COUNT, cmd_handler);
	set_handler(OPERATOR_COUNT + 1, parantheses_handler);
}

/**
 * @brief Initializes the main program structure
 *
 * @param envp
 */
void	init_struct(char **envp)
{
	t_program	*program;

	program = get_program();
	create_envp(&(program->envp), envp);
	del_from_envp(program->envp, "OLDPWD");
	program->opened_count = 0;
	init_lists();
	program->status = 0;
	program->is_on_getline = 0;
	update_shlvl();
	init_environment(program);
	if (*get_errno() != 0)
		return ;
}

static void	init_lists(void)
{
	t_program	*program;
	char		*temp;
	char		*home;

	program = get_program();
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
}
