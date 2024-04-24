/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:30 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/24 10:23:20 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	envp = get_program()->envp;
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
