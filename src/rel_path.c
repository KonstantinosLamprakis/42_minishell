/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rel_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:05:21 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/01 18:14:10 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_relative_cmd(char **cmd_args)
{
	char	*tmp;
	char	*cmd;

	cmd = get_env_value(get_program()->envp, "PWD", "/");
	if (!cmd)
		return (NULL);
	tmp = ft_strjoin(cmd, cmd_args[0]);
	free(cmd);
	if (!tmp)
		return (NULL);
	if (access(tmp, F_OK | X_OK) >= 0)
		return (tmp);
	return (free(tmp), NULL);
}
