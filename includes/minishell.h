/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/18 10:36:48 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h> // chdir, write, getcwd
# include <stdlib.h> // getenv
# include <stdio.h> // printf

typedef struct s_program
{
	char	**envp;
	char	**env_path;
	int		status;
}				t_program;

//			INIT_STRUCT.c

void		init_struct(t_program *program, char *envp);

//			QUIT_UTILS.c

void		free_arr(void **arr, int is_alloc);

#endif
