/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:21:09 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/23 20:58:05 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief finds and return the position of the key variable
 * on the envp
 *
 * @param envp the envp
 * @param key the value that it will be founded ex. "HOME"
 * @return int, position of key at envp or -1 if not founded
 */
static int	find_env(char **envp, char *key)
{
	int		i;
	int		found;
	int		k;

	if (!key || !key[0])
		return (-1);
	k = -1;
	found = 0;
	while (envp[++k] && !found)
	{
		i = 0;
		while (envp[k][i] != '\0' && key[i] != '\0' && envp[k][i] == key[i])
			i++;
		found = (key[i] == '\0' && (envp[k][i] == '=' || envp[k][i] == '\0'));
	}
	if (!found)
		return (-1);
	return (k - 1);
}

/**
 * @brief Get the value of the enviroment variable named key
 *
 * @param envp environment variables tables from main
 * @param key environment variable name ex. "HOME"
 * @param suffix optional, if its not NULL, it is added at the result
 * @return NULL if not find the value, or the value is just KEY and no
 * KEY=VALUE, otherwise the value
 * The value should be free after it used
 */
char	*get_env_value(char *envp[], char *const key, char *suffix)
{
	int		i;
	int		found;
	int		k;
	char	*result;
	char	*temp;

	k = find_env(envp, key);
	if (k == -1 || envp[k][ft_strlen(key) + 1] != '=')
		return (NULL);
	found = ft_strlen(key) + 1;
	result = malloc((ft_strlen(envp[k]) - found + 1) * sizeof(char));
	if (!result)
		return (set_error((char *)__func__, ALLOC), NULL);
	i = 0;
	while (envp[k][found] != '\0')
		result[i++] = envp[k][found++];
	result[i] = '\0';
	if (!suffix)
		return (result);
	temp = result;
	result = ft_strjoin(temp, suffix);
	free(temp);
	return (result);
}

/**
 * @brief Create a new envp, copy everything from old one and
 * then add new_var * at the end.
 * Finally free old_envp and update the pointer to point the new one.
 *
 * @param envp_ptr pointer to the env which will be updated,
 * should be freeable
 * @param new_var is the new value we add at the end
 * @param pos if is negative or grater than size of envp then
 * the new_var puted on last position otherwise it puted on position pos
 * and everythink else shifted to the right after that
 */
void	add_to_envp(char ***envp_ptr, char *new_var, int pos)
{
	int		i;
	char	**result;
	char	**envp;

	if (!envp_ptr || !*envp_ptr || !new_var)
		return ;
	envp = *envp_ptr;
	i = 0;
	while (envp[i])
		i++;
	result = malloc((i + 2) * sizeof(char *));
	if (!result)
		return (set_error((char *)__func__, ALLOC));
	i = -1;
	while (envp[++i])
		result[i] = envp[i - ((i > pos) && pos >= 0)];
	result[i] = envp[i - 1];
	if (pos > i || pos < 0)
		result[i] = ft_strdup(new_var);
	else if (pos >= 0)
		result[pos] = ft_strdup(new_var);
	result[++i] = NULL;
	free(envp);
	*envp_ptr = result;
}

/**
 * @brief delete a value from env
 *
 * @param envp
 * @param key the value that it will be delteted ex. "HOME"
 * @return returns the position of the deleted element or -1 if not found
 */
int	del_from_envp(char **envp, char *key)
{
	int	i;
	int	pos;

	if (!envp || !key)
		return (-1);
	pos = find_env(envp, key);
	if (pos == -1)
		return (-1);
	i = pos;
	free(envp[i]);
	while (envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
	return (pos);
}

/**
 * @brief change a value of a key at env
 *
 * @param envp
 * @param key the value that it will be changed ex. "HOME"
 * @param new_value contains the new value not included "="
 */
void	replace_envp_key(char ***envp, char *key, char *new_value)
{
	char	*temp;

	if (!envp || !*envp || !key || !new_value)
		return ;
	temp = ft_strjoin_3(key, "=", new_value);
	add_to_envp(envp, temp, del_from_envp(*envp, key));
	free(temp);
}
