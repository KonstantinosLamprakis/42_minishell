/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/24 09:27:18 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"

# include <unistd.h> // open, read, write, access, close, fork, dup, dup2
# include <sys/fcntl.h> // open_flags

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# ifndef CHILD_PROCESS
#  define CHILD_PROCESS 0
# endif

typedef struct s_program
{
	char	**envp;
	char	**env_path;
	int		status;
	int		opened_files[OPEN_MAX];
	int		opened_count;
	int		std_fd[3];
	char	*delimiter;
}				t_program;

//			ENV_UTILS.c

void		add_to_envp(char ***envp_ptr, char *new_var, int pos);
char		*get_env_value(char *envp[], char *const key, char *suffix);
int			del_from_envp(char **envp, char *key);
void		replace_envp_key(char ***envp, char *key, char *new_value);

//			UTILS.c

// int			builtin_execve(const char *path, char *const argv[], char *envp[]);
char		*ft_strjoin_3(char const *s1, char const *s2, char const *s3);
char		*get_line(void);

//			STRUCT_RELATED

t_program	*get_program(void);
void		init_struct(char **envp);
void		clean_struct(t_program *program);


//			UTILS

void		free_arr(char **arr, int is_alloc);
int			ft_open(char *file_name, int flags, int mode);

//			OPERATORS

int			l_redirect_handler(void *arg);
void		left_redirection(char *arg, char *left_arg);
int			l_delimiter_handler(void *arg);

//			COMMAND_RELATED

int			cmd_handler(void *arg);
void		exec_cmd(char **cmd);

//			MISC.c

void		print_opened_fd(void);
void		print_std_fd(void);
void		print_environment(void);

#endif
