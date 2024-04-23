/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:39:02 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 10:04:39 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_handler(void *arg)
{
	t_token	*token;
	char	**cmd;
	int		offset;

	token = (t_token *)arg;
	printf("\n%s: received token:\n", (char *)__func__);
	printf("  |- string: %s\n", token->str);
	cmd = ft_fctsplit(token->str, ft_iswspace);
	printf("  |- cmd:\n");
	if (cmd)
	{
		int	i = -1;
		while (cmd[++i])
			printf("    |- cmd[%d] = %s\n", i, cmd[i]);
	}
	offset = -1;
	return (offset);
}
