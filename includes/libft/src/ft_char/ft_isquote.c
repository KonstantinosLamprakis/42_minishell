/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:52:09 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 09:54:41 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"

int	ft_issquote(int c)
{
	return (c == '\'');
}

int	ft_isdquote(int c)
{
	return (c == '\"');
}

int	ft_isquote(int c)
{
	return (ft_issquote(c) || ft_isdquote(c));
}
