/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/22 16:15:44 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

typedef struct s_program
{
	char	**envp;
	char	**env_path;
	int		status;
}				t_program;

//			ENV_UTILS.c

void		add_to_envp(char ***envp_ptr, char *new_var, int pos);
char		*get_env_value(char *envp[], char *const key, char *suffix);
int			del_from_envp(char **envp, char *key);
void		replace_envp_key(char ***envp, char *key, char *new_value);

//			INIT_STRUCT.c

void		init_struct(t_program *program, char *envp);

//			QUIT_UTILS.c

void		free_arr(void **arr, int is_alloc);

#endif
