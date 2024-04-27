/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:57:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/27 22:56:38 by klamprak         ###   ########.fr       */
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

int	dollar_op(char	*str)
{
	int	i;
	char	*cmd;
	int	start;
	int	end;
	int	is_bracket;

	is_bracket = 0;
	i = -1;
	cmd = ft_strdup(str);
	while (cmd[++i])
	{
		if (cmd[i] == '$')
		{
			is_bracket += (cmd[i + 1] == '{');
			if (is_bracket)
				cmd = replace_dollar(cmd, i, '}');
			else
				cmd = replace_dollar(cmd, i, ' ');
		}
	}
}

/**
 * @brief
 *
 * @param str the string that contains the $, should be allocated because
 * this function will free it at the end
 * @param index the index that contains dollar
 * @param del the delimiter is { or ' ', for ${name} and $name
 * @return char *, new string allocated and should be freed after use.
 * this string is the same as the str but replaced the $ at the index
 * with its value
 * Returns NULL on error
 */
char	*replace_dollar(char *str, int index, char del)
{
	int		j;
	int		end;
	char	*result;
	char	*value;

	j = index + 1;
	while (str[j] && str[j] != del)
		j++;
	if (str[j] == '\0' && del == '}')
		return (free(str), NULL);
	end = j;
	// value is the value of the key at $key
}
