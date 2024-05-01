/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:03 by klamprak          #+#    #+#             */
/*   Updated: 2024/05/01 13:15:53 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_status(char *status_str);
static void	check_args(char *const argv[]);

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
	int	i;
	int	j;

	envp++;
	printf("exit\n");
	i = 0;
	while (argv[++i])
	{
		j = is_included(argv[i][0], "+-") != -1;
		while (ft_isdigit(argv[i][j]))
			j++;
		if (argv[i][j])
		{
			ft_putstr_fd("Error: invalid arg", 2);
			get_program()->status = 255;
			break ;
		}
	}
	check_args(argv);
	clean_struct();
	exit(get_program()->status);
}

static void	check_args(char *const argv[])
{
	if (argv[1] && argv[2] && get_program()->status != 255)
	{
		get_program()->status = 1;
		ft_putstr_fd("Error: too many args", 2);
	}
	else if (argv[1] && get_program()->status != 255)
		get_program()->status = get_status(argv[1]);
	if (!argv[1])
		get_program()->status = 0;
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
	if (!status_str[0])
		return (255);
	i = (status_str[0] == '-') || (status_str[0] == '+');
	while (status_str[i] && ft_isdigit(status_str[i]))
		i++;
	if (status_str[i] != '\0')
	{
		ms_perror_custom("exit", "numeric argument required", 0);
		status = 1;
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
