/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:54:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/23 12:16:17 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief reproduce the behavior of export with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_export(char *const argv[], char *envp[])
{
	return (0);
}

/**
 * @brief reproduce the behavior of unset with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_unset(char *const argv[], char *envp[])
{
	return (0);
}

/**
 * @brief reproduce the behavior of env with no options or arguments
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_env(char *const argv[], char *envp[])
{
	int	i;

	if (argv[1])
	{
		printf("Error: env should not have any options / args\n");
		return (-1);
	}
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}
