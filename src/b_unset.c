/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:14 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/25 16:35:58 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	unset_if_exists(char *key, char **ar);

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
	int			i;
	char		**ar;
	char		*temp;
	t_program	*program;

	envp = NULL;
	if (!argv[1])
		return (0);
	if (argv[1][0] == '-')
		return (printf("unset: -%c: invalid option\n", argv[1][1]), 1);
	program = get_program();
	if (argv[1][0] == '~' && argv[1][1] == '\0')
	{
		temp = get_env_value(program->loc_v, "~", NULL);
		if (!temp)
		{
			printf("unset: ~ not set\n");
			return (1);
		}
		printf("unset: `%s': not a valid identifier\n", temp);
		free(temp);
		return (1);
	}
	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			printf("unset: `%s': not a valid identifier\n", argv[i]);
			continue;
		}
		ar = program->envp;
		unset_if_exists(argv[i], ar);
		ar = program->loc_v;
		unset_if_exists(argv[i], ar);
		ar = program->exp_v;
		unset_if_exists(argv[i], ar);
	}
	return (0);
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
