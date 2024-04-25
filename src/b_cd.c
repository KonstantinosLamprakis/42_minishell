/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:16:01 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/25 09:45:56 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_final_path(char *arg, char *envp[]);
static char	*get_initial_path(char *path, char *envp[]);
static char	*remove_2_dots(char *path, int index);
static char	*remove_dot(char *path, int index);
static char	*trim_slashes(char *str, int is_alocated);

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
	char	*old_pwd;

	envp = get_program()->envp;
	if (argv[1] && argv[1][0] == '-' && argv[1][1] == '\0')
		path = get_env_value(envp, "OLDPWD", "/");
	else
		path = get_final_path(argv[1], envp);
	path = trim_slashes(path, 1);
	if (chdir(path) == -1)
	{
		printf ("Error moving to %s\n", path);
		free(path);
		return (-1);
	}
	old_pwd = get_env_value(envp, "PWD", NULL);
	if (!old_pwd)
		return (free(path), -1);
	replace_envp_key(&get_program()->envp, "OLDPWD", old_pwd);
	free(old_pwd);
	if (path[ft_strlen(path) - 1] == '/' && ft_strlen(path) > 1)
		path[ft_strlen(path) - 1] = '\0';
	replace_envp_key(&get_program()->envp, "PWD", path);
	if (argv[1] && argv[1][0] == '-' && argv[1][1] == '\0')
		printf("%s\n", path);
	free(path);
	return (0);
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
	char	*temp;
	char	*path;
	int		i;

	arg = trim_slashes(arg, 0);
	temp = get_initial_path(arg, envp);
	if (arg && (arg[0] == '/' || arg[0] == '~'))
		path = ft_strjoin(temp, arg + 1);
	else if (arg)
		path = ft_strjoin(temp, arg);
	else
		path = ft_strdup(temp);
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
	free(arg);
	return (free(temp), path);
}

/**
 * @brief trim multiple slashes // of str
 *
 * @param str
 * @param is_alocated it frees the str is this is 1
 * @return char* the returned str is alocated and should be freed
 */
static char	*trim_slashes(char *str, int is_alocated)
{
	int		i;
	int		len;
	int		j;
	char	*new_str;

	if (!str)
		return (NULL);
	len = 0;
	i = -1;
	while (str[++i])
		len += (str[i] == '/' && str[i + 1]== '/');
	len = ft_strlen(str) - len  + 1;
	new_str = malloc (sizeof(char) * len);
	if (!new_str && is_alocated)
		return (free(str), NULL);
	else if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] == '/' && str[i + 1]== '/'))
			continue;
		new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	if (is_alocated)
		free(str);
	return (new_str);
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
		return (get_env_value(envp, "HOME", "/"));
	if (path[0] == '/')
		return (ft_strdup("/"));
	if (path[0] == '~')
		return (get_env_value(get_program()->loc_v, "~", "/"));
	temp = get_env_value(envp, "PWD", "/");
	if (temp[0] == '/' && temp[1] == '/')
		return (free(temp), get_env_value(envp, "PWD", NULL));
	return (temp);
}

/**
 * @brief create a new path, as result of the current one after removing ..
 * and navigating to the parrent folder
 *
 * @param path should be allocated, because this fucntion will free it
 * @param index the index of '/' char before 2 dots, ex. /../ or /..EOF
 * @return char* it is allocated and need to be freed
 */
static char	*remove_2_dots(char *path, int index)
{
	int		i;
	int		j;
	int		start;
	char	*result;

	start = index - 1;
	while (start > 0 && path[start] != '/')
		start--;
	result = malloc((ft_strlen(path) - (path[index + 3] == '/') \
	- 1 - ((index - start - 1) * (start != -1))) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (path[++i] != '\0')
	{
		if (i > start && i <= index + 2 && i != 0)
			continue ;
		if (i == index + 3 && path[i] == '/')
			continue ;
		result[j++] = path[i];
	}
	result[j] = '\0';
	free(path);
	return (result);
}

/**
 * @brief create a new path, as result of the current one after removing .
 *
 * @param path should be allocated, because this fucntion will free it
 * @param index the index of '.' char before dot ex. /./ or /.EOF
 * @return char* it is allocated and need to be freed
 */
static char	*remove_dot(char *path, int index)
{
	int		i;
	int		j;
	char	*result;

	result = malloc((ft_strlen(path) - (path[index + 1] == '/')) \
	* sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (path[++i] != '\0')
	{
		if (i == index)
			continue ;
		if (i == index + 1 && path[i] == '/')
			continue ;
		result[j++] = path[i];
	}
	result[j] = '\0';
	free(path);
	return (result);
}
