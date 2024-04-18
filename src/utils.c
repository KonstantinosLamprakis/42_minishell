/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:21:09 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/18 11:21:49 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Get the value of the enviroment variable named key
 *
 * @param envp environment variables tables from main
 * @param key environment variable name ex. "HOME"
 * @return NULL if not find the value, otherwise the value
 * the value should be free after it used
 */
static char	*get_env_value(char *const envp[], char *const key)
{
	int		i;
	int		found;
	int		k;
	char	*result;

	k = -1;
	found = 0;
	while (envp[++k] && !found)
	{
		i = 0;
		while (envp[k][i] != '\0' && key[i] != '\0' && envp[k][i] == key[i])
			i++;
		found = (key[i] == '\0' && envp[k][i] == '=');
	}
	if (!found)
		return (NULL);
	found = i + 1;
	result = malloc(ft_strlen(envp[--k] - found) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (envp[k][found] != '\0')
		result[i++] = envp[k][found++];
	result[i] = '\0';
	return (result);
}

/**
 * @brief Create a new envp, copy everything from old one and then add new_var
 * at the end. Finally free old_envp and update the pointer to point the new one.
 *
 * @param envp_ptr pointer to the env which will be updated, should be freeable
 * @param new_var is the new value we add at the end
 */
void	add_to_envp(char ***envp_ptr, char *new_var)
{
	int		i;
	char	**result;
	char	**envp;

	if (!envp_ptr)
		return (NULL);
	envp = *envp_ptr;
	if (!envp || !new_var)
		return ;
	i = 0;
	while (envp[i])
		i++;
	result = malloc((i + 2) * sizeof(char *));
	if (!result)
		return (set_error((char *)__func__, ALLOC));
	i = -1;
	while (envp[++i])
		result[i] = envp[i];
	result[i++] = ft_strdup(new_var);
	result[i] = NULL;
	free(envp);
	*envp_ptr = result;
}
