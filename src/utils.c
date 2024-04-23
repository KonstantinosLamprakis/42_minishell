/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:09:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/23 16:49:24 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*trim_spaces_between(char *line_read, int start, int end);

/**
 * @brief same as execve but for custom built-in functions spesified by task
 * description
 *
 * @param path the name of the function ex. echo, cd, pwd, export,
 * unset, env, exit
 * @param argv name of the func and its arguments
 * @param envp enviroment variables
 * @return int, -1 on error, 0 on success
 */
int	builtin_execve(const char *path, char *const argv[], char *envp[])
{
	if (!path || !argv || !argv[0])
		return (-1);
	if (ft_strcmp(path, "echo") == 0)
		return (b_echo(argv, envp));
	else if (ft_strcmp(path, "cd") == 0)
		return (b_cd(argv, envp));
	else if (ft_strcmp(path, "pwd") == 0)
		return (b_pwd(argv, envp));
	else if (ft_strcmp(path, "export") == 0)
		return (b_export(argv, envp));
	else if (ft_strcmp(path, "unset") == 0)
		return (b_unset(argv, envp));
	else if (ft_strcmp(path, "env") == 0)
		return (b_env(argv, envp));
	else if (ft_strcmp(path, "exit") == 0)
		return (b_exit(argv, envp));
	return (-1);
}

/**
 * @brief same with strjoin but 3 args
 *
 * @param s1
 * @param s2
 * @param s3
 * @return char*
 */
char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(s1, s2);
	temp2 = ft_strjoin(temp, s3);
	free(temp);
	return (temp2);
}

/**
 * @brief Get the line object
 *
 * @return char* should free the line after use, returns NULL
 * on error, otherwise it return the line from user
 */
char	*get_line(void)
{
	char	*line_read;
	int		start;
	int		end;

	line_read = readline("minishell > ");
	if (!line_read)
		return (NULL);
	if (line_read && line_read[0] == '\0')
		return (free(line_read), NULL);
	add_history(line_read);
	start = 0;
	while (line_read[start] == ' ' || line_read[start] == '\t')
		start++;
	end = ft_strlen(line_read) - 1;
	while (end >= 0 && (line_read[end] == ' ' || line_read[end] == '\t'))
		end--;
	if (end < start)
		return (free(line_read), NULL);
	line_read = trim_spaces_between(line_read, start, end);
	return (line_read);
}

/**
 * @brief trim space and tab inside the line read, free line read
 * and return a new string allocated with malloc
 *
 * @param line_read
 * @param start 1rst not space char, index included
 * @param end last not space char, index included
 * @return char* NULL on error, trimmed string otherwise
 */
static char	*trim_spaces_between(char *line_read, int start, int end)
{
	int		i;
	int		count;
	char	*result;

	i = start - 1;
	count = 0;
	while (++i < end)
		if ((line_read[i] == ' ' || line_read[i] == '\t') && \
		(line_read[i + 1] == ' ' || line_read[i + 1] == '\t'))
			count++;
	result = malloc (sizeof(char) * (1 + end - start + 1 - count));
	if (!result)
		return (free(line_read), NULL);
	i = start - 1;
	count = 0;
	while (++i <= end)
		if (!((line_read[i] == ' ' || line_read[i] == '\t') && \
		(line_read[i + 1] == ' ' || line_read[i + 1] == '\t')))
			result[count++] = line_read[i];
	result[count] = '\0';
	free(line_read);
	return (result);
}
