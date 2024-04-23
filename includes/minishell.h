/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/23 16:12:13 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <unistd.h> // chdir, write, getcwd
# include <stdlib.h> // getenv
# include <stdio.h> // printf

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

//			INIT_STRUCT.c
void		init_struct(t_program *program, char **envp);

//			ENV_UTILS.c
void		add_to_envp(char ***envp_ptr, char *new_var, int pos);
char		*get_env_value(char *envp[], char *const key, char *suffix);
int			del_from_envp(char **envp, char *key);
void		replace_envp_key(char ***envp, char *key, char *new_value);

//			UTILS.c
char		*ft_strjoin_3(char const *s1, char const *s2, char const *s3);
int			builtin_execve(const char *pathname, char *const argv[], char *envp[]);

//			B_CD.c
int			b_cd(char *const argv[], char *envp[]);

//			BUILTIN_FUNCS.c
int			b_echo(char *const argv[], char *envp[]);
int			b_pwd(char *const argv[], char *envp[]);
int			b_exit(char *const argv[], char *envp[]);
//			UTILS.c

char		*get_line(void);

//			STRUCT_RELATED

t_program	*get_program(void);
// void		init_struct(char **envp);
void		clean_struct(t_program *program);


//			UTILS

//			BUILTIN_FUNCS_ENV.c
int			b_export(char *const argv[], char *envp[]);
int			b_unset(char *const argv[], char *envp[]);
int			b_env(char *const argv[], char *envp[]);

//			QUIT_UTILS.c
void		free_arr(void **arr, int is_alloc);
int			ft_open(char *file_name, int flags, int mode);

//			OPERATORS

int		l_redirect_handler(void *arg);
void		left_redirection(char *arg, char *left_arg);

//			MISC.c

void		print_opened_fd(void);
void		print_std_fd(void);

#endif
