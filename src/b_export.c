/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:22 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/25 21:32:29 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Edge cases:
		export test
			- test not exist (just add "test" at exp_v[] not at envp[])
			- test exists and has a value already (just export it "test=value")
		export test=
			- same as export test="", the new value is just an empty string
		export test=value
			- test not exists: create it and export it at envp[]
			- test exists and has a value already -> replace the value and
			export it at envp[]
			- value is not a valid name_value
			- in all cases should add on env whithout "", we add "" only
			when we print exported vars
		export test="value"
			- same with export test=value
		export
			- just print env and exported vars but sorted
		export name+=value
			- equal to export name= if value is NULL
			- equal to name=value if not name exists
			- equal to name=cur_valuevalue
			add value at the end of current value of name if name exits
 */

#include "../includes/minishell.h"

static int	handle_arg(char *arg);
static void	handle_eq(char *arg, int j, char *value, char *key);
static void	handle_empty(char *value, char *key);
static char	*handle_plus(char *arg, int *index, char *key);

/**
 * @brief reproduce the behavior of export with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_export(char *const argv[], char *envp[])
{
	int			i;
	t_program	*program;

	envp = NULL;
	program = get_program();
	if (!argv[1])
		return (print_sorted(program->envp, program->exp_v), 0);
	i = 0;
	while (argv[++i])
		handle_arg(argv[i]);
	return (0);
}

static int	handle_arg(char *arg)
{
	char	*value;
	char	*key;
	int		j;

	if (!ft_isalpha(arg[0]))
		return (printf("export: %s: not valid identifier\n", arg), 0);
	j = 1;
	while (ft_isalnum(arg[j]))
		j++;
	if (arg[j] != '=' && arg[j] != '\0' && \
	(arg[j] != '+' || arg[j + 1] != '='))
		return (printf("export: %s: not valid identifier\n", arg), 0);
	value = NULL;
	key = ft_substr(arg, 0, j);
	if (arg[j] == '+' && arg[j + 1] == '=')
		value = handle_plus(arg, &j, key);
	if (arg[j] == '=')
		handle_eq(arg, j, value, key);
	else
		handle_empty(value, key);
	free(key);
	return (0);
}

static void	handle_eq(char *arg, int j, char *value, char *key)
{
	if (arg[j + 1] != '\0' && !value)
		value = ft_substr(arg, j + 1, ft_strlen(arg));
	else if (!value)
		value = ft_strdup("");
	del_from_envp(get_program()->exp_v, key);
	del_from_envp(get_program()->loc_v, key);
	replace_envp_key(&get_program()->envp, key, value);
	free(value);
}

static void	handle_empty(char *value, char *key)
{
	if (!value)
		value = get_env_value(get_program()->loc_v, key, NULL);
	if (value)
	{
		del_from_envp(get_program()->loc_v, key);
		replace_envp_key(&get_program()->envp, key, value);
		free(value);
	}
	else
	{
		value = get_env_value(get_program()->envp, key, NULL);
		if (!value)
		{
			del_from_envp(get_program()->exp_v, key);
			add_to_envp(&get_program()->exp_v, key, -1);
		}
		else
			free(value);
	}
}

static char	*handle_plus(char *arg, int *index, char *key)
{
	char	*temp;
	char	*value;
	int		j;

	j = *index;
	value = NULL;
	if (arg[j + 2] == '\0')
		j++;
	else
	{
		temp = get_env_value(get_program()->envp, key, NULL);
		if (!temp)
			temp = get_env_value(get_program()->loc_v, key, NULL);
		if (!temp)
			j++;
		else
		{
			value = ft_strjoin(temp, arg + j + 2);
			free(temp);
			j++;
		}
	}
	*index = j;
	return (value);
}
