/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:57:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/27 21:38:40 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- Cases:
		- name=
			- if exists empty its value, else coninue
		- name="     value  a"
			- same as name = "value a"
		- name=value
			- create the name with this value
		- name+=value
			- if name not exists it create it, else add value at its end
		- name=$name2
			- just replace $name2 with its content and run the initial assigment
	- Errors
		-$name=value
			- replace $name with its content and execute the whole command
			content=value: command not found
		-"name"=value
			- name=value: command not found

*/

#include "../includes/minishell.h"

/**
 * @brief assigment operator ex. test1=adsfas
 *
 * @param argv a list like ["test1=fsdfg", "test2=fsdfg"]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	exec_assign(char *const argv[], char *envp[])
{
	int	i;
	int	status;

	envp = NULL;
	status = 0;
	if (!argv || !argv[0])
		return (-1);
	i = -1;
	while (argv[++i])
		if (argv[i][0])
			status += handle_arg(argv[i], 0);
	return (-1 * (status != 0));
}

/**
 * @brief
 *
 * @param argv a list like ["test1=fsdfg", "test2=fsdfg"]
 * @return int returns 1 if this comand is an assigment command,
 * 0 otherwise
 */
int	is_assign(char *const argv[])
{
	int	i;
	int	j;

	i = -1;
	if (!argv || !argv[0])
		return (0);
	while (argv[++i])
	{
		if (!argv[i][0])
			continue ;
		j = 0;
		j += (argv[i][0] == '$');
		if (!ft_isalpha(argv[i][j]) && argv[i][j] != '_')
			return (0);
		while (ft_isalnum(argv[i][j]))
			j++;
		j += (argv[i][j] == '+');
		if (argv[i][j] != '=')
			return (0);
	}
	return (1);
}
