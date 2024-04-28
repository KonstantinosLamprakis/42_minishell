/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:16:01 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/28 23:07:49 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_final_path(char *arg, char *envp[]);
static char	*get_initial_path(char *path, char *envp[]);
static char	*get_path(char *arg, char *envp[]);
static int	change_dir(char *path, char **envp);

/*
	Edge cases:
		- cd
			- after HOME is useted
		- cd /../../../../../././././
		- cd -
		- cd ~
			- even if home is unseted
		- cd ../////../////
 */

/**
 * @brief reproduce the behavior of cd with only a relative-absolute path
 * no need to free the result of getenv
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_cd(char *const argv[], char *envp[])
{
	char	*path;

	envp = get_program()->envp;
	if (argv[1] && argv[1][0] == '-' && argv[1][1] == '\0')
	{
		path = get_env_value(envp, "OLDPWD", "/");
		if (!path)
			return (fprintf(stderr, "cd: OLDPWD not set\n"), -1);
	}
	else
		path = get_final_path(argv[1], envp);
	path = trim_slashes(path, 1);
	if (!path)
		return (-1);
	if (change_dir(path, envp) == -1)
		return (-1);
	if (argv[1] && argv[1][0] == '-' && argv[1][1] == '\0')
		printf("%s\n", path);
	free(path);
	return (0);
}

static int	change_dir(char *path, char **envp)
{
	char	*old_pwd;

	if (chdir(path) == -1)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", path);
		if (path)
			free(path);
		return (-1);
	}
	old_pwd = get_env_value(envp, "PWD", NULL);
	replace_envp_key(&get_program()->envp, "OLDPWD", old_pwd);
	if (old_pwd)
		free(old_pwd);
	if (path[ft_strlen(path) - 1] == '/' && ft_strlen(path) > 1)
		path[ft_strlen(path) - 1] = '\0';
	replace_envp_key(&get_program()->envp, "PWD", path);
	return (1);
}

/**
 * @brief Get the initial path which will be home folder if
 * not args provided at cd, pwd folder if path is relative
 * or "/" root folder if path is absolute
 *
 * @param path
 * @param envp
 * @return char*
 */
static char	*get_initial_path(char *path, char *envp[])
{
	char	*temp;

	if (!path)
	{
		temp = get_env_value(envp, "HOME", "/");
		if (!temp)
			fprintf(stderr, "cd: HOME not set\n");
		return (temp);
	}
	if (path[0] == '/')
		return (ft_strdup("/"));
	if (path[0] == '~')
	{
		temp = get_env_value(get_program()->loc_v, "~", "/");
		if (!temp)
			fprintf(stderr, "unset: ~ not set\n");
		return (temp);
	}
	temp = get_env_value(envp, "PWD", "/");
	if (!temp)
		return (fprintf(stderr, "cd: PWD not set\n"), NULL);
	return (temp);
}

/**
 * @brief Get the final path after geting initiale one
 * and replace .., . and relative to absolute
 *
 * @param path
 * @param envp
 * @return char*
 */
static char	*get_final_path(char *arg, char *envp[])
{
	char	*path;
	int		i;

	path = get_path(arg, envp);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i] != '\0')
	{
		if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '.' \
		&& (path[i + 3] == '/' || path[i + 3] == '\0'))
			path = remove_2_dots(path, i);
		else if (path[i] == '/' && path[i + 1] == '.' \
		&& (path[i + 2] == '/' || path[i + 2] == '\0'))
			path = remove_dot(path, i + 1);
		else
			continue ;
		i = -1;
	}
	return (path);
}

static char	*get_path(char *arg, char *envp[])
{
	char	*temp;
	char	*path;

	arg = trim_slashes(arg, 0);
	temp = get_initial_path(arg, envp);
	if (!temp)
		return (NULL);
	if (arg && (arg[0] == '/' || arg[0] == '~'))
		path = ft_strjoin(temp, arg + 1);
	else if (arg)
		path = ft_strjoin(temp, arg);
	else
		path = ft_strdup(temp);
	free(temp);
	free(arg);
	return (path);
}
