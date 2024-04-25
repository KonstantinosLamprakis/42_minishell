/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:00:08 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/25 17:23:41 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Frees everything in arr until NULL is reached
 *
 * @param arr
 * @param is_alloc whether or not arr is allocated
 */
void	free_arr(void **arr, int is_alloc)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	// if (arr)
	// 	while (*arr)
	// 		free(*arr++);
	if (is_alloc)
		free(arr);
}
