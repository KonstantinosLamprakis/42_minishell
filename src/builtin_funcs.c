/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:50:56 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/23 12:22:38 by klamprak         ###   ########.fr       */
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
		- echo -nnnnnn, echo -n -n -n echo test > out1 > out2, creates out1
		and out2 but writes test only at out2
		- implement cd to work with . and ..
		- in order to free from signal you just call a function which contains
		a static variable as pointer to the things you want to free.
		This pointer initialized at the beggining
		- env, var SHLVL
			- -42 -> negative became "0"
			- 42 -> number became number + 1 = 43
			- "test" -> remains test
		- export
			- without args -> print env but sorted
			- export abc+=" something here"
			- if you do export test
				- at export you will se test='' but at env you will not
				see the test at all
		- use bash as referece -> just type bash at terminal
		- should I modify putstr to return -1 on error of the write function?
		- exit() should clean fd and memory before exit
		- what to do with unset? should be exported to environment variables
		in order to access the local variables of the shell
		- unset should have extra command to add assigment to local vars
		implement the whole thing locally (export command and assigment)
		- env should also print local vars that are exported
		- consider local exported vars whenever we use env in other commands
		- add null check at strdup, strcmp, strjoin, putstr, strlen, substr
 */

/**
 * @brief reproduce the behavior of echo with option -n
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_echo(char *const argv[], char *envp[])
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
 * @brief reproduce the behavior of pwd no options
 * filename has max length of 260
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_pwd(char *const argv[], char *envp[])
{
	char	s[261];

	if (!getcwd(s, 261))
		return (-1);
	if (ft_putstr(s) == -1)
		return (-1);
	return (0);
}

/**
 * @brief reproduce the behavior of exit with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_exit(char *const argv[], char *envp[])
{
	int	status;
	int	i;

	printf("exit\n");
	if (argv[1] && argv[2])
	{
		printf("exit: too many arguments\n");
		return (-1);
	}
	if (argv[1])
	{
		i = -1 + (argv[1][0] == '-');
		while (argv[1][++i] != '\0')
			if (argv[1][i] < '0' || argv[1][i] > '9')
				break;
		if (argv[1][i] != '\0')
		{
			printf("exit: %s: numeric argument required\n", argv[1]);
			// status = same as the last command executed
		}
		else
		{
			status = ft_atoi(argv[1]);
			if (status < 0)
				status = 256 - (-status % 256);
			else if (status > 255)
				status = status % 256;
			if (status == 256)
				status = 0;
		}
	}
	// free everything
	exit(status);
}
