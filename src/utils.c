/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:09:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/26 17:06:05 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		return (b_echo(argv, envp));
	else if (ft_strcmp(path, "cd") == 0)
		return (b_cd(argv, envp));
	else if (ft_strcmp(path, "pwd") == 0)
		return (b_pwd(argv, envp));
	else if (ft_strcmp(path, "export") == 0)
		return (b_export(argv, envp));
	else if (ft_strcmp(path, "unset") == 0)
		return (b_unset(argv, envp));
	else if (ft_strcmp(path, "env") == 0)
		return (b_env(argv, envp));
	else if (ft_strcmp(path, "exit") == 0)
		return (b_exit(argv, envp));
	return (-2);
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

/**
 * @brief Get the line object
 * readline returns NULL if Ctrl D received and "\0" if empty
 * command received
 *
 * @return char* should free the line after use, returns NULL
 * on error, otherwise it return the line from user
 */
char	*get_line(void)
{
	char	*line_read;

	line_read = readline("minishell > ");
	if (!line_read)
	{
		clean_struct();
		exit(0);
	}
	else if (!line_read[0])
		return (free(line_read), NULL);
	add_history(line_read);
	return (line_read);
}
