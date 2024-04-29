/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:36 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/29 10:06:59 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_option_n(char *const argv[], int *i);
static void	echo_arg(char *arg);

/*
	edge cases:
		- echo -nnnnnnn -n -n -n test
		- echo
		- echo -nnnnnnnadsfasdf -n -n -n test
		- echo -asdfadsf
		- echo ~
			- even if home is unseted
*/

/**
 * @brief reproduce the behavior of echo with option -n
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_echo(char *const argv[], char *envp[])
{
	int		is_n;
	int		i;

	envp++;
	i = 0;
	is_n = is_option_n(argv, &i);
	if (!argv[i])
		return (0);
	i--;
	while (argv[++i])
	{
		echo_arg(argv[i]);
		if (argv[i + 1])
			printf(" ");
	}
	if (!is_n)
		printf("\n");
	return (0);
}

static void	echo_arg(char *arg)
{
	char	*temp;
	char	*str;

	if (arg[0] == '~' && (arg[1] == '/' || arg[1] == '\0'))
	{
		temp = get_env_value(get_program()->loc_v, "~", NULL);
		str = ft_strjoin(temp, arg + 1);
		printf("%s", str);
		if (temp)
			free(temp);
		free(str);
	}
	else
		printf("%s", arg);
}

/**
 * @brief returns if there is option -n and bypass it
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param i when returned, points to the 1st valid argument
 * which is not -n option
 * @return int 0 if not option -n, 1 otherwise
 */
static int	is_option_n(char *const argv[], int *i)
{
	int	j;
	int	is_n;

	if (!argv[1])
	{
		printf("\n");
		*i = 1;
		return (0);
	}
	is_n = 0;
	while (argv[++(*i)])
	{
		if (argv[*i][0] != '-' || argv[*i][1] != 'n')
			break ;
		j = 2;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] != '\0')
			break ;
		is_n = 1;
	}
	return (is_n);
}
