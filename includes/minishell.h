/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/30 16:42:01 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> // signals
#include <sys/types.h> // waitpid for linuc
#include <sys/wait.h> // waitpid for linuc
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>    // getenv
# include <strings.h>   // SIGINT, SIGOUT
# include <sys/fcntl.h> // open_flags
# include <unistd.h>    // chdir, write, getcwd open, read, write, access, close, fork, dup, dup2, pause
# include <errno.h>

# define ERROR_PROMPT "minishell"
# define SYNTAX_ERR_MSG "syntax error near unexpected token"
# define CMD_NF_ERR_MSG "command not found"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define STDCOUNT 3

# define MAX_SUB_DEPTH 256

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

// FOPEN_MAX: for lunux
// OPEN_MAX: for MAC
typedef struct s_program
{
	char			**envp;
	char			**loc_v;
	char			**exp_v;
	char			**env_path;
	int				status;
	int				opened_files[FOPEN_MAX];
	int				opened_count;
	int				std_fd[3];
	char			*delimiter;
	int				pipe_end[2];
	int				is_piped;
	int				pipe_save_write[MAX_SUB_DEPTH];
	int				pipe_save_read[MAX_SUB_DEPTH];
	int				depth;
	int				is_on_getline;
}					t_program;

# define SYNTAX_STATUS 2
# define CMD_NF_STATUS 127
# define NO_FD_STATUS 1

typedef int			(*t_operator_handler)(void *);

typedef enum e_operators
{
	AND,
	OR,
	PIPE,
	L_REDIRECT,
	R_REDIRECT,
	L_DELIMITER,
	R_APPEND,
	OPERATOR_COUNT
}					t_operators;

typedef enum e_encapsulators
{
	L_PARANTHESE,
	R_PARANTHESE,
	ENCAPSULATOR_COUNT
}					t_encapsulators;

# define AND_OP "&&"
# define OR_OP "||"
# define PIPE_OP "|"
# define L_REDIRECT_OP "<"
# define R_REDIRECT_OP ">"
# define L_DELIMITER_OP "<<"
# define R_APPEND_OP ">>"

# define L_PARANTHESE_ENC "("
# define R_PARANTHESE_ENC ")"

typedef struct s_token
{
	char			*str;
	t_operators		op;
	t_encapsulators	enc;
	int				start;
	int				end;
}					t_token;

//			UTILS2.c
int			skip_quotes(char const *str, char quote);
char		*replace_quotes(char *str);

//			CUSTOM_SPLIT.c
char				**ft_split_custom(char const *s, char c);

//			ASSIGN_OP.c

int					is_assign(char *const argv[]);
int					exec_assign(char *const argv[], char *envp[]);

//			DOLLAR_OP.c

char				*dollar_op(char *str);

//			SIGNALS.c

void				handler_idle(int sig);
void				handler_cmd(int sig);
void				handler_exit(int sig);

//			ENV_UTILS.c

void				add_to_envp(char ***envp_ptr, char *new_var, int pos);
char				*get_env_value(char *envp[], char *const key, char *suffix);
int					del_from_envp(char **envp, char *key);
void				replace_envp_key(char ***envp, char *key, char *new_value);
int					find_env(char **envp, char *key);

//			ENV_UTILS_2.c

void				create_envp(char ***new_envp, char **old_envp);

//			UTILS.c

char				*ft_strjoin_3(char const *s1, char const *s2,
						char const *s3);
int					builtin_execve(const char *pathname, char *const argv[],
						char *envp[]);
char				*get_line(void);
int					is_builtin(char *path);
void				set_status(int status);
int					contains_op(char *str);
int					ft_strop(char *str);
void				ms_perror(char *arg, int ft_errno);
void				ms_perror_custom(char *arg, char *msg, int ft_errno);
void				ms_syntax_error(char *arg);
void				ms_cmdnf_error(char *arg);
char				**ft_escsplit(char *str, int (*cmp)(int), int (*esc)(int));

//			BUILTIN FUNCS

int					b_cd(char *const argv[], char *envp[]);
int					b_echo(char *const argv[], char *envp[]);
int					b_pwd(char *const argv[], char *envp[]);
int					b_exit(char *const argv[], char *envp[]);
int					b_export(char *const argv[], char *envp[]);
int					b_unset(char *const argv[], char *envp[]);
int					b_env(char *const argv[], char *envp[]);
int					is_valid_name(char *name, int start);

//			B_CD_UTILS

char				*trim_slashes(char *str, int is_alocated);
char				*remove_2_dots(char *path, int index);
char				*remove_dot(char *path, int index);

//			B_EXPORT_UTILS

int					handle_arg(char *arg, int is_exp);
void				handle_eq(char *arg, char *value, char *key, int is_exp);
char				*handle_plus(char *arg, int *index, char *key);

//			STRUCT_RELATED

t_program			*get_program(void);
void				init_struct(char **envp);
void				clean_struct(void);

//			QUIT_UTILS.c

void				free_arr(char **arr, int is_alloc);
int					ft_open(char *file_name, int flags, int mode);
int					ft_open_first(char *file_name, int flags, int mode);

//			CLEAN_STRUCT.c

void				clean_struct(void);
void				reset_struct(void);
void				reset_std_fd(void);
void				close_opened_files(void);

//			OPERATORS

int					l_redirect_handler(void *arg);
void				left_redirection(char *arg, char *left_arg);

int					l_delimiter_handler(void *arg);
void				left_delimiter(char *arg);

int					and_handler(void *arg);
void				and_operation(char *left_arg);

int					or_handler(void *arg);
void				or_operation(char *left_arg);

int					pipe_handler(void *arg);
void				pipe_operation(char *left_arg);

int					r_redirect_handler(void *arg);
void				right_redirection(char *arg, char *left_arg);

int					r_append_handler(void *arg);
void				right_append(char *arg, char *left_arg);

int					parantheses_handler(void *arg);

//			COMMAND_RELATED

char				*get_cmd(char **cmd_args);
int					cmd_handler(void *arg);
void				exec_cmd(char **cmd);

//			MISC.c

void				print_opened_fd(void);
void				print_std_fd(void);
void				print_environment(void);

//			PARSER

void				ft_parse(char *str);

int					find_next_token(char *str, t_token *token);

int					handle_found_operator(t_token *token, int index,
						t_operators op);
int					handle_found_encapsulator(t_token *token, char *str,
						int start, t_encapsulators enc);

char				**get_operators(void);
char				**get_encapsulators(void);
int					*get_lengths(void);

int					ft_is_operator(char *str, int op);
int					ft_which_op(char *str);
int					ft_which_enc(char *str);

int					ft_is_encapsulator(int c);
int					endof_paranthese(char *str, int start);

t_operator_handler	*get_handlers(void);
void				set_handler(t_operators op, t_operator_handler new_handler);

#endif
