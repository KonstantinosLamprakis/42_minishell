/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:55:43 by klamprak          #+#    #+#             */
/*   Updated: 2024/05/01 15:23:26 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define LEFT_BRACKET '{'
#define RIGHT_BRACKET '}'

static char	*replace_dollar(char *str, int *index, char del);
static char	*put_value(char *str, int *index, char *key, char *value);
static char	*get_value(char *key);
static void	handle_dollar(char **cmd, int *i, int *is_bracket);

/*
	- Cases $
		- $name: if name exists at loc_v or envp replace it with its value else with ""
		replace until space ' '
		- ${name}: replace until }
		- $? : replace it with the get_program()->status
		- "$test"
*/

/**
 * @brief checks for $ and replace it with its value
 *
 * @param str
 * @return char* it is allocated and it is the new command that should be
 * executed after it replaced $key with its value
 */
char	*dollar_op(char	*str)
{
	int		i;
	char	*cmd;
	int		is_bracket;
	int		is_quote;

	is_bracket = 0;
	i = -1;
	cmd = ft_strdup(str);
	is_quote = 0;
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '\'')
			is_quote = !is_quote;
		if (cmd[i] == '$' && !is_quote)
			handle_dollar(&cmd, &i, &is_bracket);
	}
	return (cmd);
}

static void	handle_dollar(char **cmdp, int *i, int *is_bracket)
{
	char	*cmd;

	cmd = *cmdp;
	if (is_included(cmd[*i + 1], "\'\"") != -1)
		if (is_included(cmd[*i + 2], " \t") != -1 || !cmd[*i + 2])
			return ;
	if (is_included(cmd[*i + 1], " \t") != -1 || !cmd[*i + 1])
		return ;
	*is_bracket += (cmd[*i + 1] == LEFT_BRACKET);
	if (*is_bracket)
		*cmdp = replace_dollar(cmd, i, RIGHT_BRACKET);
	else
		*cmdp = replace_dollar(cmd, i, ' ');
	*is_bracket = 0;
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
 * Returns NULL on error (key not found, ${name, )
 */
static char	*replace_dollar(char *str, int *index, char del)
{
	int		j;
	int		end;
	char	*result;
	char	*value;
	char	*key;

	j = *index + 1 + (del == RIGHT_BRACKET);
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	if (str[j] == '?')
		j++;
	if (del == RIGHT_BRACKET && str[j] != del)
		return (free(str), NULL);
	end = j;
	j = *index + 1 + (del == RIGHT_BRACKET);
	key = ft_substr(str, j, end - j);
	if (!key)
		return (free(str), NULL);
	value = get_value(key);
	result = put_value(str, index, key, value);
	free(str);
	free(value);
	free(key);
	return (result);
}

/**
 * @brief get value of key at $key=value
 * if key not exists return '\0'
 *
 * @param key
 * @return char*
 */
static char	*get_value(char *key)
{
	char	*value;

	value = NULL;
	if (key[0] == '?' && key[1] == '\0')
		value = ft_itoa(get_program()->status);
	else
		value = get_env_value(get_program()->envp, key, NULL);
	if (!value)
		value = get_env_value(get_program()->loc_v, key, NULL);
	if (!value)
		value = ft_strdup("");
	return (value);
}

/**
 * @brief put replace $name at str with the value, and replace the new
 * str, which is allocated at memory
 *
 * @param str
 * @param index str[index] is equal to '$' symbol
 * @param key the name of the variable ex. $key
 * @param value the value of the variable ex. $key=value
 * @return char* the new str that contains the value instead of $key
 * or NULL if allocation error occured
 */
static char	*put_value(char *str, int *index, char *key, char *value)
{
	int		i;
	int		j;
	int		k;
	char	del;
	char	*result;

	del = RIGHT_BRACKET + (str[*index + 1] != LEFT_BRACKET);
	result = malloc(sizeof(char) * (1 + ft_strlen(str) + ft_strlen(value) \
	- ft_strlen(key) - 1 - 2 * (del == RIGHT_BRACKET)));
	if (!result)
		return (set_error((char *)__func__, ALLOC), NULL);
	i = 0;
	j = 0;
	while (str[i] && i < *index)
		result[j++] = str[i++];
	k = 0;
	while (value[k])
		result[j++] = value[k++];
	i += 1 + 2 * (del == RIGHT_BRACKET) + ft_strlen(key);
	*index = j - 1;
	while (str && str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	return (result);
}
