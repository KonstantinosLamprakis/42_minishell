/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:19 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/28 23:07:49 by klamprak         ###   ########.fr       */
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
		fprintf(stderr, "pwd: %c%c: invalid option\n", argv[1][0], argv[1][1]);
		return (-1);
	}
	path = get_env_value(envp, "PWD", NULL);
	if (!path)
	{
		fprintf(stderr, "pwd: PWD not set\n");
		return (-1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
