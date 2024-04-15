/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:05:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/10 08:13:20 by lgreau           ###   ########.fr       */
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
	int	old_value;

	ft_errno = get_errno();
	old_value = *ft_errno;
	*ft_errno = err_value;
	if (old_value != err_value)
		ft_perror();
}
