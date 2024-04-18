/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:50:56 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/18 11:27:04 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	INFO:
		- in case of echo without -n option, should be consider an error
		or just do the normal echo? -> I did normal echo
		- in case of cd, should I consider options like -L, also should I
		consider if path is missing to take path from $HOME? ->
		didn't consider any options and also I implement the functionality
		with $HOME

	TODO:
		- should I modify putstr to return -1 on error of the write function?
		- exit() should clean fd and memory before exit
		- what to do with unset? should be exported to environment variables
		in order to access the local variables of the shell
		- unset should have extra command to add assigment to local vars
		implement the whole thing locally (export command and assigment)
		- env should also print local vars that are exported
		- consider local exported vars whenever we use env in other commands
 */

/**
 * @brief reproduce the behavior of echo with option -n
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_echo(char *const argv[], char *const envp[])
{
	int	is_n;
	int	i;

	is_n = ft_strcmp("-n", argv[1]) == 0;
	i = is_n;
	while (argv[++i])
	{
		if (ft_putstr(argv[i]) == -1)
			return (0);
		if (argv[i + 1])
			if (write(1, " ", 1) == -1)
				return (-1);
	}
	if (!is_n)
		if (write(1, "\n", 1) == -1)
			return (-1);
	return (0);
}

/**
 * @brief reproduce the behavior of cd with only a relative-absolute path
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_cd(char *const argv[], char *const envp[])
{
	char	*path;
	int		i;

	path = argv[1];
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
			return (-1);
		chdir(path);
	}
	return (chdir(argv[1]));
}

/**
 * @brief reproduce the behavior of pwd no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_pwd(char *const argv[], char *const envp[])
{
	char	s[261];

	if (!getcwd(s, 261))
		return (-1);
	if (ft_putstr(s) == -1)
		return (-1);
	return (0);
}

/**
 * @brief reproduce the behavior of export with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_export(char *const argv[], char *const envp[])
{
	return (0);
}

/**
 * @brief reproduce the behavior of unset with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_unset(char *const argv[], char *const envp[])
{
	return (0);
}


/**
 * @brief reproduce the behavior of env with no options or arguments
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_env(char *const argv[], char *const envp[])
{
	int		i;

	if (argv[1])
	{
		printf("Error: env should not have any options / args\n");
		return (-1);
	}
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}


/**
 * @brief reproduce the behavior of exit with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_exit(char *const argv[], char *const envp[])
{
	if (argv[1])
	{
		printf("Error: exit should not have any options / args\n");
		return (-1);
	}
	exit(0);
}

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
int	builtin_execve(const char *pathname, char *const argv[], char *const envp[])
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

int	main(int argc, char **argv, char **envp)
{
	argv++;
	builtin_execve(argv[0], argv, envp);
}
