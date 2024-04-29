/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_custom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/29 16:41:08 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_result(char **mem_str, int *k);
static char	*update_mem_str(char **mem_str, int i, char **result);
static void	put_buffer(char buffer[BUFFER_SIZE], int num_bytes, char **mem_str);
static char	*get_whole_str(char **mem_str);
static char	*get_first_line(char **mem_str);

char	*ft_get_next_line_custom(int fd)
{
	char		buffer[BUFFER_SIZE];
	char		*result;
	static char	*mem_str = NULL;
	int			num_bytes;

	result = get_first_line(&mem_str);
	if (result)
		return (result);
	while (42)
	{
		if (get_program()->status == 130 || get_program()->status == 131)
		{
			if (mem_str)
				free(mem_str);
			return (NULL);
		}
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
		{
			if (mem_str)
				free(mem_str);
			mem_str = NULL;
			return (NULL);
		}
		put_buffer(buffer, num_bytes, &mem_str);
		result = get_first_line(&mem_str);
		if (result)
			return (result);
		if (num_bytes < BUFFER_SIZE)
			return (get_whole_str(&mem_str));
	}
}

// puts first num_butes of buffer at the end of mem_str
// if error returns NULL
// if mem_str == NULL, it creates it
static void	put_buffer(char buffer[BUFFER_SIZE], int num_bytes, char **mem_str)
{
	int		i;
	int		j;
	char	*temp_str;

	if (!buffer || num_bytes == 0)
		return ;
	if (buffer[0] == '\0')
		return ;
	j = ft_strlen(*mem_str);
	temp_str = malloc ((j + num_bytes + 1) * sizeof (char));
	if (!temp_str)
		return ;
	i = 0;
	while (i < j)
	{
		temp_str[i] = (*mem_str)[i];
		i++;
	}
	j = 0;
	while (j < num_bytes)
		temp_str[i++] = buffer[j++];
	temp_str[i] = '\0';
	if (*mem_str)
		free(*mem_str);
	*mem_str = temp_str;
}

// free the mem_str and returns a new identical string
static char	*get_whole_str(char **mem_str)
{
	char	*result;
	int		i;

	if (!(*mem_str))
		return (NULL);
	result = malloc((ft_strlen(*mem_str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while ((*mem_str)[i] != '\0')
	{
		result[i] = (*mem_str)[i];
		i++;
	}
	result[i] = '\0';
	free(*mem_str);
	*mem_str = NULL;
	return (result);
}

// return NULL if mem_str == NUL or mem_str not contain any new line
// return the first new line of mem_str and updates mem_str with the rest of it
static char	*get_first_line(char **mem_str)
{
	int		i;
	char	*result;

	result = get_result(mem_str, &i);
	if (!result)
		return (NULL);
	if ((*mem_str)[i + 1] == '\0')
	{
		free(*mem_str);
		*mem_str = NULL;
		return (result);
	}
	return (update_mem_str(mem_str, i, &result));
}

static char	*update_mem_str(char **mem_str, int i, char **result)
{
	char	*temp_mem_str;
	int		j;

	temp_mem_str = malloc((ft_strlen(*mem_str) - i) * sizeof(char));
	if (!temp_mem_str)
	{
		free(*result);
		return (NULL);
	}
	j = 0;
	while ((*mem_str)[++i] != '\0')
		temp_mem_str[j++] = (*mem_str)[i];
	temp_mem_str[j] = '\0';
	free (*mem_str);
	*mem_str = temp_mem_str;
	return (*result);
}

static char	*get_result(char **mem_str, int *k)
{
	char	*result;
	int		i;
	int		j;

	i = *k;
	if (!(*mem_str))
		return (NULL);
	i = 0;
	while ((*mem_str)[i] != '\0' && (*mem_str)[i] != '\n')
		i++;
	if ((*mem_str)[i] == '\0')
		return (NULL);
	result = malloc ((i + 2) * sizeof(char));
	if (!result)
		return (NULL);
	j = -1;
	while (++j <= i)
		result[j] = (*mem_str)[j];
	result[j] = '\0';
	*k = i;
	return (result);
}
