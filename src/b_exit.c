/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/30 21:05:11 by klamprak         ###   ########.fr       */
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

	envp++;
	// ft_putstr_fd("exit\n", 1);
	printf("exit\n");
	if (argv[1] && argv[2])
	{
		ms_perror_custom("exit", "too many arguments", 0);
		return (-1);
	}
	if (argv[1])
		status = get_status(argv[1]);
	else
		status = 0;
	clean_struct();
	get_program()->status = status;
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
		ms_perror_custom("exit", "numeric argument required", 0);
		status = get_program()->status;
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
