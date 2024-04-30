/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:28:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 13:36:15 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_perror(char *arg, int ft_errno)
{
	set_errno(ft_errno);
	if (errno != NO_ERROR)
		printf("%s: %s: %s\n", ERROR_PROMPT, arg, strerror(errno));
}

void	ms_syntax_error(char *arg)
{
	set_status(SYNTAX_STATUS);
	set_errno(SYNTAX);
	printf("%s: ", ERROR_PROMPT);
	printf("%s `%1s'\n", SYNTAX_ERR_MSG, arg);
}
