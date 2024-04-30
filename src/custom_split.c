/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:57:23 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/30 14:19:10 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:14:19 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/08 17:11:38 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_result(char const *str, char sep, char **result);
static void	free_mem(int k, char	**result);
static char	*get_str(char const *str, int start, int end);
static int	count_seps(char const *str, char sep);

char	**ft_split_custom(char const *s, char c)
{
	char	**result;
	int		k;
	int		i;

	result = malloc((count_seps(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	k = get_result(s, c, result);
	i = 0;
	while (i < k)
	{
		if (result[i] == NULL)
		{
			free_mem(k, result);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[k] = NULL;
	return (result);
}

static void	free_mem(int k, char	**result)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (result[i] != NULL)
			free(result[i]);
		i++;
	}
}

/**
 * @brief returns the substring from start included, until end
 * excluded
 *
 * @param str
 * @param start
 * @param end
 * @return char*
 */
static char	*get_str(char const *str, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (start < end)
	{
		result[i] = str[start];
		start++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	count_seps(char const *str, char sep)
{
	int	i;
	int	sep_c;

	i = 0;
	sep_c = 0;
	while (str[i] != '\0' && str[i] == sep)
		i++;
	if (str[i] != '\0')
		sep_c++;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += skip_quotes(str + i, str[i]);
		if (str[i] == sep && str[i + 1] != sep && str[i + 1] != '\0')
			sep_c++;
		i++;
	}
	return (sep_c);
}

/**
 * @brief create the whole table and it returns it
 *
 * @param str
 * @param sep
 * @param result
 * @return int returns the nummber of the words
 */
static int	get_result(char const *str, char sep, char **result)
{
	int	i;
	int	k;
	int	start;
	int	is_sep;

	i = 0;
	start = 0;
	k = 0;
	is_sep = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += skip_quotes(str + i, str[i]);
		is_sep = (str[i] == sep);
		if (is_sep)
		{
			if (start != i)
				result[k++] = get_str(str, start, i);
			start = i + 1;
		}
		i++;
	}
	if (!is_sep)
		result[k++] = get_str(str, start, i);
	return (k);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char **result;
// 	result = ft_split("....This.is.a.fucking.", '.');
// 	// result = ft_split("a  a  a", ' ');
// 	while (*result != NULL)
// 	{
// 		printf("%s\n", *result);
// 		result++;
// 	}
// }


// #include "ft_string.h"

// static int	count_words(char *str, int (*cmp)(int), int (*esc)(int))
// {
// 	int	index;
// 	int	count;
// 	int	tmp;

// 	index = -1;
// 	count = (!(*cmp)(str[0]) || (*esc)(str[0]));
// 	while (str[++index])
// 	{
// 		if ((*esc)(str[index]))
// 		{
// 			count++;
// 			tmp = str[index++];
// 			while (str[index] && str[index] != tmp)
// 				index++;
// 			if (!str[index])
// 				return (-1);
// 		}
// 		else if (index > 0 && ft_isword(str + index - 1, cmp))
// 			count++;
// 	}
// 	return (count);
// }

// static void	free_arr(char **arr, int is_allocated)
// {
// 	if (arr)
// 		while (arr)
// 			free(*arr++);
// 	if (is_allocated)
// 		free(arr);
// }

// static int	save_word(char **arr, char *str, int *count, int (*cmp)(int))
// {
// 	char	*tmp;

// 	tmp = ft_strchr_if(str + 1, cmp);
// 	arr[(*count)++] = ft_substr_if(str, 0, tmp - str, cmp);
// 	if (!arr[(*count) - 1])
// 		set_error((char *)__func__, ALLOC);
// 	return (*get_errno());
// }

// static void	fill_arr(char **arr, char *str, int (*cmp)(int), int (*esc)(int))
// {
// 	int		index;
// 	int		wc;
// 	char	*tmp;

// 	index = -1;
// 	wc = 0;
// 	if ((!(*cmp)(str[0]) && !(*esc)(str[0])) && save_word(arr, str + ++index,
// 			&wc, cmp) != 0)
// 		return ;
// 	while (str[++index])
// 	{
// 		if ((*esc)(str[index]))
// 		{
// 			tmp = ft_strchr(str + index + 1, str[index]);
// 			if (!tmp)
// 				return (set_error((char *)__func__, SYNTAX));
// 			arr[wc++] = ft_substr(str, index + 1, tmp - (str + index) - 1);
// 			if (!arr[wc - 1])
// 				return (free_arr(arr, 1), set_error((char *)__func__, ALLOC));
// 			index += (tmp - (str + index) + 1);
// 		}
// 		else if (index > 0 && ft_isword(str + index - 1, cmp) && save_word(arr,
// 				str + index, &wc, cmp) != 0)
// 			return ;
// 	}
// }

// /**
//  * @brief Splits str by the cmp == 1 characters
//  * while respecting the esc == 1 characters
//  *
//  * @param str
//  * @param cmp
//  * @param esc
//  * @return char**
//  */
// char	**ft_escsplit(char *str, int (*cmp)(int), int (*esc)(int))
// {
// 	char	**res;
// 	int		wc;

// 	if (!str || !cmp || !esc)
// 		return (set_error((char *)__func__, INVALID_ARG), NULL);
// 	wc = count_words(str, cmp, esc);
// 	res = ft_calloc(wc + 1, sizeof(char *));
// 	if (!res)
// 		return (set_error((char *)__func__, ALLOC), NULL);
// 	fill_arr(res, str, cmp, esc);
// 	if (*get_errno() != 0)
// 		return (NULL);
// 	return (res);
// }
