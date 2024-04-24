/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:19 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/24 10:22:03 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief reproduce the behavior of pwd no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_pwd(char *const argv[], char *envp[])
{
	char	*path;

	envp = get_program()->envp;
	if (argv[1] && argv[1][0] == '-')
	{
		printf("Error: should not provide any option with pwd command\n");
		return (-1);
	}
	path = get_env_value(envp, "PWD", NULL);
	if (!path)
		return (-1);
	printf("%s\n", path);
	free(path);
	return (0);
}
