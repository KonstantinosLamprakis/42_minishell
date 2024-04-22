/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:38:40 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/22 15:33:31 by klamprak         ###   ########.fr       */
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

//			BUILTIN_FUNCS_ENV.c
int			b_export(char *const argv[], char *envp[]);
int			b_unset(char *const argv[], char *envp[]);
int			b_env(char *const argv[], char *envp[]);

//			QUIT_UTILS.c
void		free_arr(void **arr, int is_alloc);

#endif
