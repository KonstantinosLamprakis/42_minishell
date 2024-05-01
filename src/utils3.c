/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:28:18 by klamprak          #+#    #+#             */
/*   Updated: 2024/05/01 15:51:49 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief copy everything from old_envp to new_envp
 *
 * @param new_envp pointer to new envp
 * @param old_envp old envp that we will copy to the new one
 */
void	create_envp(char ***new_envp, char **old_envp)
{
	int		i;
	int		j;
	char	**result;

	if (!old_envp)
		return ;
	i = 0;
	while (old_envp[i])
		i++;
	result = malloc((i + 1) * sizeof(char *));
	if (!result)
		return (set_error((char *)__func__, ALLOC));
	i = -1;
	while (old_envp[++i])
	{
		result[i] = malloc(sizeof(char) * (ft_strlen(old_envp[i]) + 1));
		if (!result[i])
			return (free(result), set_error((char *)__func__, ALLOC));
		j = -1;
		while (old_envp[i][++j] != '\0')
			result[i][j] = old_envp[i][j];
		result[i][j] = '\0';
	}
	result[i] = NULL;
	*new_envp = result;
}

void	update_shlvl(void)
{
	char	*value;
	int		i;
	int		shlvl;

	value = get_env_value(get_program()->envp, "SHLVL", NULL);
	if (!value)
	{
		replace_envp_key(&get_program()->envp, "SHLVL", "1");
		return ;
	}
	i = 0;
	while (value[i] >= '0' && value[i] <= '9')
		i++;
	if (value[i] != '\0' || i > 10)
		shlvl = 0;
	else
		shlvl = ft_atoi(value);
	shlvl++;
	free(value);
	value = ft_itoa(shlvl);
	replace_envp_key(&get_program()->envp, "SHLVL", value);
	free(value);
}

/**
 * @brief Get the line object
 * readline returns NULL if Ctrl D received and "\0" if empty
 * command received
 *
 * @return char* should free the line after use, returns NULL
 * on error, otherwise it return the line from user
 */
char	*get_line(void)
{
	char	*line_read;

	if (!isatty(fileno(stdin)))
		return (ft_get_next_line_nonl(fileno(stdin)));
	while (42)
	{
		get_program()->is_on_getline = 1;
		line_read = readline("minishell > ");
		get_program()->is_on_getline = 0;
		if (!line_read)
		{
			clean_struct();
			exit(0);
		}
		else if (!line_read[0])
			free(line_read);
		else
			break ;
	}
	add_history(line_read);
	return (line_read);
}
