/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:56:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/25 22:06:44 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief sorts the array that is NULL terminated
 *
 * @param ar
 */
void	sort_array(char **ar)
{
	int		i;
	int		j;
	char	*temp;
	int		swaped;

	if (!ar || !ar[0] || !ar[1])
		return ;
	i = -1;
	swaped = 1;
	while (ar[++i] && swaped)
	{
		j = 0;
		swaped = 0;
		while (ar[j] && ar[j + 1])
		{
			if (ft_strcmp(ar[j], ar[j + 1]) > 0)
			{
				temp = ar[j];
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
				swaped = 1;
			}
			j++;
		}
	}
}

/**
 * @brief prints a record for the export command
 *
 * @param rec
 */
void	print_record(char *rec)
{
	int	i;
	int	is_eq;

	i = -1;
	is_eq = 0;
	printf("declare -x ");
	while (rec[++i] != '\0')
	{
		printf("%c", rec[i]);
		if (rec[i] == '=' && !is_eq)
			printf("\"");
		is_eq += rec[i] == '=';
	}
	if (is_eq)
		printf("\"");
	printf("\n");
}

/**
 * @brief takes 2 arrays, sort them temporary, print and print them sorted
 *
 * @param p_envp
 * @param p_exp_v
 */
void	print_sorted(char **p_envp, char **p_exp_v)
{
	char		**envp;
	char		**exp_v;
	int			i;
	int			j;

	create_envp(&envp, p_envp);
	create_envp(&exp_v, p_exp_v);
	sort_array(envp);
	sort_array(exp_v);
	i = 0;
	j = 0;
	while (envp[i] && exp_v[j])
	{
		if (ft_strcmp(envp[i], exp_v[j]) < 0)
			print_record(envp[i++]);
		else
			print_record(exp_v[j++]);
	}
	while (exp_v[j] && !envp[i])
		print_record(exp_v[j++]);
	while (envp[i] && !exp_v[j])
		print_record(envp[i++]);
	free_arr(envp, 1);
	free_arr(exp_v, 1);
}
