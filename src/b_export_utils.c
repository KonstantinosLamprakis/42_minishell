/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:56:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/30 15:47:27 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_empty(char *value, char *key);
static void	handle_assign(char *value, char *key);

/**
 * @brief handles each arg of the export command or the assign command
 * ex. "export test1=x test2=y" has 2 args "test1=x" and "test2=y"
 *
 * @param arg ex. "test1=value"
 * @param is_exp 1 if its called from export command, 0 if called from assign
 * @return int 0 on success, 1 on error
 */
int	handle_arg(char *arg, int is_exp)
{
	char	*value;
	char	*key;
	int		j;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (fprintf(stderr, "export: %s: not valid identifier\n", arg), 1);
	j = 1;
	while (ft_isalnum(arg[j]) || arg[j] == '_')
		j++;
	if (arg[j] != '=' && arg[j] != '\0' && \
	(arg[j] != '+' || arg[j + 1] != '='))
		return (fprintf(stderr, "export: %s: not valid identifier\n", arg), 1);
	value = NULL;
	key = ft_substr(arg, 0, j);
	if (arg[j] == '+' && arg[j + 1] == '=')
		value = handle_plus(arg, &j, key);
	if (arg[j] == '=')
		handle_eq(arg + j, value, key, is_exp);
	else if (is_exp)
		handle_empty(value, key);
	free(key);
	return (0);
}

/**
 * @brief handle the case of "export test=value"
 * Also handle the case of test+=value after handle_plus()
 * @param arg the command ex. "test=value_here"
 * @param value the value of the key, if is calculated so far
 * ex. from handle_plus() func
 * @param key the name of the variable
 * @param is_exp 1 if its called from export command, 0 if its
 * called from simple assign ex. "test=10 vs export test=10"
 */
void	handle_eq(char *arg, char *value, char *key, int is_exp)
{
	if (arg[1] != '\0' && !value)
	{
		if (!(ft_strlen(arg) >= 3 && (arg[1] == '\"' && arg[2] == '\"')))
			value = ft_substr(arg, 1, ft_strlen(arg));
	}
	else if (!value)
		value = ft_strdup("");
	if (is_exp)
	{
		del_from_envp(get_program()->exp_v, key);
		del_from_envp(get_program()->loc_v, key);
		replace_envp_key(&get_program()->envp, key, value);
	}
	else
		handle_assign(value, key);
	free(value);
}

static void	handle_assign(char *value, char *key)
{
	if (find_env(get_program()->exp_v, key) != -1)
	{
		del_from_envp(get_program()->exp_v, key);
		replace_envp_key(&get_program()->envp, key, value);
	}
	else if (find_env(get_program()->loc_v, key) != -1)
		replace_envp_key(&get_program()->loc_v, key, value);
	else if (find_env(get_program()->envp, key) != -1)
		replace_envp_key(&get_program()->envp, key, value);
	else
		replace_envp_key(&get_program()->loc_v, key, value);
}

/**
 * @brief handle the case of "export test+=value"
 *
 * @param arg the command ex. "test+=conca_value_here"
 * @param index update the current position at the command with
 * + 1 if there is a '+'. New index will point at '='
 * @param key the name of the variable
 * @return the new value of the variable, which will be the old
 * one with the suffix of the command's value
 */
char	*handle_plus(char *arg, int *index, char *key)
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

/**
 * @brief handle the case of "export test"
 *
 * @param value the value of the variable if exists so far
 * @param key the name of the variable
 */
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
