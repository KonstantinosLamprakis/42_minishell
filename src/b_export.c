/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:22 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/26 19:37:37 by klamprak         ###   ########.fr       */
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

static void	print_sorted(char **p_envp, char **p_exp_v);
static void	print_record(char *rec);
static void	sort_array(char **ar);

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
	int			status;

	envp = NULL;
	status = 0;
	program = get_program();
	if (!argv[1])
		return (print_sorted(program->envp, program->exp_v), 0);
	i = 0;
	while (argv[++i])
		status += handle_arg(argv[i], 1);
	return (-1 * (status != 0));
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
		return ;
	i = -1;
	swaped = 1;
	while (ar[++i] && swaped)
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
	if (is_eq)
		printf("\"");
	printf("\n");
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
	while (envp[i] && exp_v[j])
	{
		if (ft_strcmp(envp[i], exp_v[j]) < 0)
			print_record(envp[i++]);
		else
			print_record(exp_v[j++]);
	}
	while (exp_v[j] && !envp[i])
		print_record(exp_v[j++]);
	while (envp[i] && !exp_v[j])
		print_record(envp[i++]);
	free_arr(envp, 1);
	free_arr(exp_v, 1);
}
