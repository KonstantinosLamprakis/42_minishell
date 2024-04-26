/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:44:42 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 12:01:55 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

void	set_error(char *caller_name, int ft_errno)
{
	int	old_errno;

	set_error_caller(caller_name);
	old_errno = *get_errno();
	set_errno(ft_errno);
	if (old_errno != *get_errno())
		printf("%s%s\n", ft_strerror(*get_errno()), *get_error_caller());
}
