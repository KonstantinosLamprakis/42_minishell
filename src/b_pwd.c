/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:19 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/30 18:35:26 by klamprak         ###   ########.fr       */
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
		ms_perror_custom("pwd", argv[1], INVALID_OPT);
		return (-1);
	}
	path = get_env_value(envp, "PWD", NULL);
	if (!path)
	{
		ms_perror_custom("pwd", "PWD", ENV_NOT_SET);
		return (-1);
	}
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	return (0);
}
