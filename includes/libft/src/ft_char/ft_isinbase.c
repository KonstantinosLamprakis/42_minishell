/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinbase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:16:33 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:35:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"

int	ft_isinbase(int c, char *base)
{
	return (ft_strchr(base, c) != NULL);
}

int	ft_isinbasen(int c, char *base, int n)
{
	if (ft_strchr(base, c) == NULL)
		return (0);
	return ((ft_strchr(base, c) - base) < n);
}
