/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:09:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/18 13:20:09 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief same with strjoin but 3 args
 *
 * @param s1
 * @param s2
 * @param s3
 * @return char*
 */
char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(s1, s2);
	temp2 = ft_strjoin(temp, s3);
	free(temp);
	return (temp2);
}
