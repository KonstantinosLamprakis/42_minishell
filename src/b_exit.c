/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/23 16:38:14 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_status(char *status_str);

/*
	Edge cases:
		- exit
		- exit adsf fadsf
		- exit 10 adsfasd
		- exit -10
 */

/**
 * @brief reproduce the behavior of exit with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_exit(char *const argv[], char *envp[])
{
	int	status;

	envp = NULL;
	printf("exit\n");
	if (argv[1] && argv[2])
	{
		printf("exit: too many arguments\n");
		return (-1);
	}
	if (argv[1])
		status = get_status(argv[1]);
	else
		status = 0;
	// TODO free everything
	exit(status);
}

/**
 * @brief Get the status of the 1rst argument, or 0 if not valid
 *
 * @param status_str , 1rst arg that indicated the status
 * @return int status
 */
static int	get_status(char *status_str)
{
	int	i;
	int	status;

	status = 0;
	i = -1 + (status_str[0] == '-');
	while (status_str[++i] != '\0')
		if (status_str[i] < '0' || status_str[i] > '9')
			break ;
	if (status_str[i] != '\0')
	{
		printf("exit: %s: numeric argument required\n", status_str);
		// TODO status = same as the last command executed
	}
	else
	{
		status = ft_atoi(status_str);
		if (status < 0)
			status = 256 - (-status % 256);
		else if (status > 255)
			status = status % 256;
		if (status == 256)
			status = 0;
	}
	return (status);
}
