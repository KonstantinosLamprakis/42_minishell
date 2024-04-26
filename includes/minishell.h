/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/26 09:42:24 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h> // chdir, write, getcwd
# include <stdlib.h> // getenv
#include <signal.h> // signals
#include <strings.h> // SIGINT, SIGOUT

# include <unistd.h> // open, read, write, access, close, fork, dup, dup2, pause
# include <sys/fcntl.h> // open_flags

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define STDCOUNT 3

/*
	envp: an always up-to-date array that holds environment vars
	loc_v: same as envp but only for local vars that are not env
	and not displayed either at "env" or "export", only at "$(var)"
	exp_v: same as envp but only for exported vars, with no value
	that they are not displayed at normal "env", only at "export"
	status: the status of the last command that excecuted
 */
# ifndef CHILD_PROCESS
#  define CHILD_PROCESS 0
# endif

# define HERE_DOC_FILE ".here_doc_tmp"
# define HERE_DOC_PROMPT "heredoc> "

# define PIPE_WRITE 1
# define PIPE_READ 0

typedef struct s_program
{
	char	**envp;
	char	**loc_v;
	char	**exp_v;
	char	**env_path;
	int		status;
	int		opened_files[OPEN_MAX];
	int		opened_count;
	int		std_fd[3];
	char	*delimiter;
	int		pipe_end[2];
}				t_program;

//			SIGNALS.c

int			init_signal(void);
void		put_signal_handler(int is_idle);

//			ENV_UTILS.c

void		add_to_envp(char ***envp_ptr, char *new_var, int pos);
char		*get_env_value(char *envp[], char *const key, char *suffix);
int			del_from_envp(char **envp, char *key);
void		replace_envp_key(char ***envp, char *key, char *new_value);

//			ENV_UTILS_2.c

void		create_envp(char ***new_envp, char **old_envp);

//			UTILS.c

char		*ft_strjoin_3(char const *s1, char const *s2, char const *s3);
int			builtin_execve(const char *pathname, char *const argv[], \
			char *envp[]);
char		*get_line(void);
int		is_builtin(char *path);

//			BUILTIN FUNCS

int			b_cd(char *const argv[], char *envp[]);
int			b_echo(char *const argv[], char *envp[]);
int			b_pwd(char *const argv[], char *envp[]);
int			b_exit(char *const argv[], char *envp[]);
int			b_export(char *const argv[], char *envp[]);
int			b_unset(char *const argv[], char *envp[]);
int			b_env(char *const argv[], char *envp[]);

//			B_CD_UTILS

char		*trim_slashes(char *str, int is_alocated);
char		*remove_2_dots(char *path, int index);
char		*remove_dot(char *path, int index);

//			B_EXPORT_UTILS

void		sort_array(char **ar);
void		print_record(char *rec);
void		print_sorted(char **p_envp, char **p_exp_v);

//			STRUCT_RELATED

t_program	*get_program(void);
void		init_struct(char **envp);
void		clean_struct(void);

//			QUIT_UTILS.c

void		free_arr(char **arr, int is_alloc);
int			ft_open(char *file_name, int flags, int mode);
int			ft_open_first(char *file_name, int flags, int mode);

//			CLEAN_STRUCT.c

void		clean_struct(void);
void		reset_struct(void);
void		reset_std_fd(void);
void		close_opened_files(void);

//			OPERATORS

int			l_redirect_handler(void *arg);
void		left_redirection(char *arg, char *left_arg);

int			l_delimiter_handler(void *arg);
void		left_delimiter(char *arg, char *left_arg);

int			and_handler(void *arg);
void		and_operation(char *left_arg);

int			or_handler(void *arg);
void		or_operation(char *left_arg);

int			pipe_handler(void *arg);
void		pipe_operation(char *left_arg);

//			COMMAND_RELATED

char		*get_cmd(char **cmd_args);
int			cmd_handler(void *arg);
void		exec_cmd(char **cmd);

//			MISC.c

void		print_opened_fd(void);
void		print_std_fd(void);
void		print_environment(void);

#endif
