/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:01:14 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/29 11:05:11 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_op(char *str)
{
	int		index;

	index = -1;
	while (str[++index])
		if (ft_which_op(str + index) >= 0 || ft_which_enc(str + index) >= 0)
			return (1);
	return (0);
}
