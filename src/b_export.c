/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:22 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/24 08:14:02 by klamprak         ###   ########.fr       */
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
 */

#include "../includes/minishell.h"

static void	sort_array(char **ar);
static void	print_record(char *rec);
static void	print_sorted(char **p_envp, char **p_exp_v);

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
	int			j;
	t_program	*program;
	char		*key;
	char		*value;

	envp = NULL;
	program = get_program();
	if (!argv[1])
		return (print_sorted(program->envp, program->exp_v), 0);
	i = 0;
	while (argv[++i])
	{
		if (!ft_isalpha(argv[i][0]))
		{
			printf("export: %s: not valid identifier\n", argv[i]);
			continue ;
		}
		j = 1;
		while (ft_isalnum(argv[i][j]))
			j++;
		if (argv[i][j] != '=' && argv[i][j] != '\0')
		{
			printf("export: %s: not valid identifier\n", argv[i]);
			continue ;
		}
		key = ft_substr(argv[i], 0, j);
		if (argv[i][j] == '=' && argv[i][j + 1] != '\0')
		{
			value = ft_substr(argv[i], j + 1, ft_strlen(argv[i]));
			del_from_envp(program->exp_v, key);
			del_from_envp(program->loc_v, key);
			replace_envp_key(&program->envp, key, value);
		}
		else if (argv[i][j] == '=')
		{
			value = ft_strdup("");
			del_from_envp(program->exp_v, key);
			del_from_envp(program->loc_v, key);
			replace_envp_key(&program->envp, key, value);
		}
		else
		{
			value = get_env_value(program->loc_v, key, NULL);
			if (!value)
				continue ;
			replace_envp_key(&program->envp, key, value);
		}
	}
	return (0);
}

/**
 * @brief takes 2 arrays, sort them temporary, print and print them sorted
 *
 * @param p_envp
 * @param p_exp_v
 */
static void	print_sorted(char **p_envp, char **p_exp_v)
{
	char		**envp;
	char		**exp_v;
	int			i;
	int			j;

	create_envp(&envp, p_envp);
	create_envp(&exp_v, p_exp_v);
	sort_array(envp);
	sort_array(exp_v);
	i = 0;
	j = 0;
	while (envp[i] || exp_v[j])
	{
		if (!envp[i])
			print_record(exp_v[j++]);
		else if (!exp_v[j])
			print_record(envp[i++]);
		if (!envp[i] || !exp_v[j])
			continue ;
		if (ft_strcmp(envp[i], exp_v[j]) < 0)
			print_record(envp[i++]);
		else
			print_record(exp_v[j++]);
	}
	free(envp);
	free(exp_v);
}

/**
 * @brief sorts the array that is NULL terminated
 *
 * @param ar
 */
static void	sort_array(char **ar)
{
	int		i;
	int		j;
	char	*temp;
	int		swaped;

	if (!ar || !ar[0] || !ar[1])
		return;
	i = 0;
	swaped = 1;
	while (ar[i] && swaped)
	{
		j = 0;
		swaped = 0;
		while (ar[j] && ar[j + 1])
		{
			if (ft_strcmp(ar[j], ar[j + 1]) > 0)
			{
				temp = ar[j];
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
				swaped = 1;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief prints a record for the export command
 *
 * @param rec
 */
static void	print_record(char *rec)
{
	int	i;
	int	is_eq;

	i = -1;
	is_eq = 0;
	printf("declare -x ");
	while (rec[++i] != '\0')
	{
		printf("%c", rec[i]);
		if (rec[i] == '=' && !is_eq)
			printf("\"");
		is_eq += rec[i] == '=';
	}
	printf("\"\n");
}
