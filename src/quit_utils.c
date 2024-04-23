/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:00:08 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 14:34:11 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Frees everything in arr until NULL is reached
 *
 * @param arr
 * @param is_alloc whether or not arr is allocated
 */
void	free_arr(char **arr, int is_alloc)
{
	if (arr)
		while (*arr)
			free(*arr++);
	if (is_alloc)
		free(arr);
}
