/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:27:32 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/25 19:44:49 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_non_slash(char *str, char *dst);

/**
 * @brief trim multiple slashes // of str
 *
 * @param str
 * @param is_alocated it frees the str is this is 1
 * @return char* the returned str is alocated and should be freed,
 * NULL on error
 */
char	*trim_slashes(char *str, int is_alocated)
{
	int		i;
	int		len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = 0;
	i = -1;
	while (str[++i])
		len += (str[i] == '/' && str[i + 1] == '/');
	len = ft_strlen(str) - len + 1;
	new_str = malloc (sizeof(char) * len);
	if (!new_str && is_alocated)
	{
		free(str);
		return (set_error((char *)__func__, ALLOC), NULL);
	}
	else if (!new_str)
		return (NULL);
	fill_non_slash(str, new_str);
	if (is_alocated)
		free(str);
	return (new_str);
}

static void	fill_non_slash(char *str, char *dst)
{
	int	j;
	int	i;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] == '/' && str[i + 1] == '/'))
			continue ;
		dst[j++] = str[i];
	}
	dst[j] = '\0';
}

/**
 * @brief create a new path, as result of the current one after removing ..
 * and navigating to the parrent folder
 *
 * @param path should be allocated, because this fucntion will free it
 * @param index the index of '/' char before 2 dots, ex. /../ or /..EOF
 * @return char* it is allocated and need to be freed
 */
char	*remove_2_dots(char *path, int index)
{
	int		i;
	int		j;
	int		start;
	char	*result;

	start = index - 1;
	while (start > 0 && path[start] != '/')
		start--;
	result = malloc((ft_strlen(path) - (path[index + 3] == '/') \
	- 1 - ((index - start - 1) * (start != -1))) * sizeof(char));
	if (!result)
		return (set_error((char *)__func__, ALLOC), NULL);
	i = -1;
	j = 0;
	while (path[++i] != '\0')
	{
		if (i > start && i <= index + 2 && i != 0)
			continue ;
		if (i == index + 3 && path[i] == '/')
			continue ;
		result[j++] = path[i];
	}
	result[j] = '\0';
	free(path);
	return (result);
}

/**
 * @brief create a new path, as result of the current one after removing .
 *
 * @param path should be allocated, because this fucntion will free it
 * @param index the index of '.' char before dot ex. /./ or /.EOF
 * @return char* it is allocated and need to be freed
 */
char	*remove_dot(char *path, int index)
{
	int		i;
	int		j;
	char	*result;

	result = malloc((ft_strlen(path) - (path[index + 1] == '/')) \
	* sizeof(char));
	if (!result)
		return (set_error((char *)__func__, ALLOC), NULL);
	i = -1;
	j = 0;
	while (path[++i] != '\0')
	{
		if (i == index)
			continue ;
		if (i == index + 1 && path[i] == '/')
			continue ;
		result[j++] = path[i];
	}
	result[j] = '\0';
	free(path);
	return (result);
}
