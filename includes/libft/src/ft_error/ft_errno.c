/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:05:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 10:45:38 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

int	*get_errno(void)
{
	static int	ft_errno = 0;

	return (&ft_errno);
}

void	set_errno(int err_value)
{
	int	*ft_errno;

	ft_errno = get_errno();
	*ft_errno = err_value;
}
