/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:09:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/05/01 15:52:42 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_in_pipe(const char *path, char *const argv[]);

/**
 * @brief check if the name path is in builtin commands
 *
 * @param path
 * @return int 0 if not builtin, 1 if it is builin, 2
 * if it is exit
 */
int	is_builtin(char *path)
{
	if (!path || !path[0])
		return (0);
	if (ft_strcmp(path, "echo") == 0)
		return (1);
	else if (ft_strcmp(path, "cd") == 0)
		return (1);
	else if (ft_strcmp(path, "pwd") == 0)
		return (1);
	else if (ft_strcmp(path, "export") == 0)
		return (1);
	else if (ft_strcmp(path, "unset") == 0)
		return (1);
	else if (ft_strcmp(path, "env") == 0)
		return (1);
	else if (ft_strcmp(path, "exit") == 0)
		return (2);
	return (0);
}

/**
 * @brief same as execve but for custom built-in functions spesified by task
 * description
 *
 * @param path the name of the function ex. echo, cd, pwd, export,
 * unset, env, exit
 * @param argv name of the func and its arguments
 * @param envp enviroment variables
 * @return int, -1 on error, 0 on success, -2 if this is not builtin func
 */
int	builtin_execve(const char *path, char *const argv[], char *envp[])
{
	if (!path || !argv || !argv[0] || !envp)
		return (-1);
	if (ft_strcmp(path, "echo") == 0)
		return (exec_in_pipe(path, argv), get_program()->status);
	else if (ft_strcmp(path, "cd") == 0)
		return (b_cd(argv, envp));
	else if (ft_strcmp(path, "pwd") == 0)
		return (exec_in_pipe(path, argv), get_program()->status);
	else if (ft_strcmp(path, "export") == 0 && !argv[1])
		return (exec_in_pipe(path, argv), get_program()->status);
	else if (ft_strcmp(path, "export") == 0)
		return (b_export(argv, envp));
	else if (ft_strcmp(path, "unset") == 0)
		return (b_unset(argv, envp));
	else if (ft_strcmp(path, "env") == 0)
		return (exec_in_pipe(path, argv), get_program()->status);
	else if (ft_strcmp(path, "exit") == 0)
		return (b_exit(argv, envp));
	return (-2);
}

static void	exec_in_pipe(const char *path, char *const argv[])
{
	pid_t	p;

	p = fork();
	if (p < 0)
		return (set_error((char *)__func__, FORK));
	else if (p == 0)
	{
		if (get_program()->is_piped)
		{
			if (dup2(get_program()->pipe_save_write[get_program()->depth], STDOUT) < 0)
				return (set_error((char *)__func__, DUP));
			close(get_program()->pipe_save_read[get_program()->depth]);
		}
		if (ft_strcmp(path, "echo") == 0)
			get_program()->status = (b_echo(argv, get_program()->envp));
		else if (ft_strcmp(path, "env") == 0)
			get_program()->status = (b_env(argv, get_program()->envp));
		else if (ft_strcmp(path, "pwd") == 0)
			get_program()->status = (b_pwd(argv, get_program()->envp));
		else if (ft_strcmp(path, "export") == 0 && !argv[1])
			get_program()->status = (b_export(argv, get_program()->envp));
		exit(get_program()->status);
	}
	waitpid(p, &get_program()->status, 0);
}

/**
 * @brief same with strjoin but 3 args
 *
 * @param s1
 * @param s2
 * @param s3
 * @return char*
 */
char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(s1, s2);
	temp2 = ft_strjoin(temp, s3);
	free(temp);
	return (temp2);
}

void	set_status(int status)
{
	get_program()->status = status;
}
