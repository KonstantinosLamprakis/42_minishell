/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/19 11:38:08 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <unistd.h> // open, read, write, access, close, fork, dup, dup2
# include <sys/fcntl.h> // open_flags

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_program
{
	char	**envp;
	char	**env_path;
	int		status;
	int		opened_files[OPEN_MAX];
	int		opened_count;
	int		std_fd[3];
}				t_program;

//			STRUCT_RELATED

t_program	*get_program(void);
void		init_struct(char **envp);
void		clean_struct(t_program *program);


//			UTILS

void		free_arr(void **arr, int is_alloc);
int			ft_open(char *file_name, int flags, int mode);

//			OPERATORS

int		l_redirect_handler(void *arg);
void		left_redirection(char *arg, char *left_arg);

//			MISC.c

void		print_opened_fd(void);
void		print_std_fd(void);

#endif
