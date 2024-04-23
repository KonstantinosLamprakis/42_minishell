/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:09:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/22 19:22:17 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief same as execve but for custom built-in functions spesified by task
 * description
 *
 * @param pathname the name of the function ex. echo, cd, pwd, export,
 * unset, env, exit
 * @param argv name of the func and its arguments
 * @param envp enviroment variables
 * @return int, -1 on error, 0 on success
 */
int	builtin_execve(const char *pathname, char *const argv[], char *envp[])
{
	if (!pathname || !argv || !argv[0])
		return (-1);
	if (ft_strcmp(pathname, "echo") == 0)
		return (b_echo(argv, envp));
	else if (ft_strcmp(pathname, "cd") == 0)
		return (b_cd(argv, envp));
	else if (ft_strcmp(pathname, "pwd") == 0)
		return (b_pwd(argv, envp));
	else if (ft_strcmp(pathname, "export") == 0)
		return (b_export(argv, envp));
	else if (ft_strcmp(pathname, "unset") == 0)
		return (b_unset(argv, envp));
	else if (ft_strcmp(pathname, "env") == 0)
		return (b_env(argv, envp));
	else if (ft_strcmp(pathname, "exit") == 0)
		return (b_exit(argv, envp));
	return (-1);
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
