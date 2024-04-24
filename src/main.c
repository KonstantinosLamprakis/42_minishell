/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 08:09:09 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	argc = 0;
	argv = NULL;
	init_struct(envp);
	set_handler(L_REDIRECT, l_redirect_handler);
	set_handler(OPERATOR_COUNT, cmd_handler);

	char	str[] = "< Makefile cat";

	ft_parse(str);

	exit(*get_errno() != 0);
}

