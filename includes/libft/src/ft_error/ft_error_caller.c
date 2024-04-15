/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_caller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:23:03 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/10 07:54:37 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

char	**get_error_caller(void)
{
	static char	*error_caller = "";

	return (&error_caller);
}

void	set_error_caller(char *caller_name)
{
	char	**error_caller;

	error_caller = get_error_caller();
	*error_caller = caller_name;
}
