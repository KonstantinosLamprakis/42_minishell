/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:56:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/27 19:20:55 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_empty(char *value, char *key);

int	handle_arg(char *arg, int is_exp)
{
	char	*value;
	char	*key;
	int		j;

	printf("args: %s\n", arg);
	if (!ft_isalpha(arg[0]))
		return (printf("export: %s: not valid identifier\n", arg), 1);
	j = 1;
	while (ft_isalnum(arg[j]) || arg[j] == '_')
		j++;
	if (arg[j] != '=' && arg[j] != '\0' && \
	(arg[j] != '+' || arg[j + 1] != '='))
		return (printf("export: %s: not valid identifier\n", arg), 1);
	value = NULL;
	key = ft_substr(arg, 0, j);
	if (arg[j] == '+' && arg[j + 1] == '=')
		value = handle_plus(arg, &j, key, is_exp);
	if (arg[j] == '=')
		handle_eq(arg + j, value, key, is_exp);
	else
		handle_empty(value, key);
	free(key);
	return (0);
}

void	handle_eq(char *arg, char *value, char *key, int is_exp)
{
	is_exp++;
	if (arg[1] != '\0' && !value)
	{
		if (!(ft_strlen(arg) >= 3 && (arg[1] == '\"' && arg[2] == '\"')))
			value = ft_substr(arg, 1, ft_strlen(arg));
	}
	else if (!value)
		value = ft_strdup("");
	del_from_envp(get_program()->exp_v, key);
	del_from_envp(get_program()->loc_v, key);
	replace_envp_key(&get_program()->envp, key, value);
	free(value);
}

char	*handle_plus(char *arg, int *index, char *key, int is_exp)
{
	char	*temp;
	char	*value;
	int		j;

	is_exp++;
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
