/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:14 by klamprak          #+#    #+#             */
/*   Updated: 2024/05/01 12:51:52 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	unset_if_exists(char *key, char **ar);
static void	unset_all_lists(char *key);
static int	not_valid_args(char *const argv[]);

/*
	Edge cases:
		- unset:
			- do nothing
		- unset [name] [name2] ...
			- delete every name if exists from any place, local, env, exported
			- if name doesn't exists just continue
		- unset -adsfds : -a: invalid option, return 1
		- unset dasf -asdf: not a valid identifier, return 1
 */

/**
 * @brief reproduce the behavior of unset with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_unset(char *const argv[], char *envp[])
{
	int	i;

	envp++;
	i = not_valid_args(argv);
	if (i != -1)
		return (i);
	i = 0;
	while (argv[++i])
	{
		if (!is_valid_name(argv[i], 0))
		{
			ms_perror_custom("unset", argv[i], INVALID_IDENTIFIER);
			get_program()->status = 1;
		}
		else
			unset_all_lists(argv[i]);
	}
	return (0);
}

static int	not_valid_args(char *const argv[])
{
	char	*temp;

	if (!argv[1])
	{
		get_program()->status = 0;
		return (0);
	}
	if (argv[1][0] == '-')
	{
		get_program()->status = 2;
		return (ms_perror_custom("unset", argv[1], INVALID_OPT), 1);
	}
	if (argv[1][0] == '~' && argv[1][1] == '\0')
	{
		temp = get_env_value(get_program()->loc_v, "~", NULL);
		if (!temp)
			return (ms_perror_custom("unset", "~", ENV_NOT_SET), 1);
		ms_perror_custom("unset", temp, INVALID_IDENTIFIER);
		return (free(temp), 1);
	}
	return (-1);
}

static void	unset_all_lists(char *key)
{
	unset_if_exists(key, get_program()->envp);
	unset_if_exists(key, get_program()->loc_v);
	unset_if_exists(key, get_program()->exp_v);
}

/**
 * @brief deletes from array ar the key if exists
 *
 * @param key key to search ex. "HOME", "PWD", "test"
 * @param ar could be either envp, array with local variables or
 * array with exported variables
 * @return int 1 if found the key and deleted, 0 if not found it
 */
static int	unset_if_exists(char *key, char **ar)
{
	int	j;

	if (!key || !key[0] || !ar)
		return (0);
	j = -1;
	while (ar[++j])
		if (del_from_envp(ar, key) != -1)
			return (1);
	return (0);
}

/**
 * @brief check if a name is a valid identifier, started with
 * [a-z][A-Z] or '_' and after containing only these or [0-9]
 *
 * @param name the name to check
 * @param start starting point included
 * @return int 0 if not valid, 1 if valid
 */
int	is_valid_name(char *name, int start)
{
	int	i;

	if (!name)
		return (1);
	i = start;
	if (ft_isalpha(name[i]) || name[i] == '_')
		i++;
	else
		return (0);
	while (ft_isalnum(name[i]) || name[i] == '_')
		i++;
	if (name[i] != '\0')
		return (0);
	return (1);
}
